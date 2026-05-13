import { fuelColorScale, formatMW, responsivefy, tooltip } from "../utils/helpers.js";

const WIDTH = 900;
const HEIGHT = 520;
const DETAIL_THRESHOLD = 2.6;

export class PowerMap {
  constructor({ el, world, countryCentroids }) {
    this.root = d3.select(el);
    this.world = world;
    this.countryCentroids = countryCentroids;
    this.currentZoom = 1;
    this.filteredPlants = [];

    this.svg = this.root.append("svg").attr("class", "power-map");
    responsivefy(this.svg, WIDTH, HEIGHT);

    this.projection = d3.geoNaturalEarth1().fitSize([WIDTH, HEIGHT], world);
    this.geoPath = d3.geoPath(this.projection);
    this.radiusScale = d3.scaleSqrt().range([3, 40]);
    this.detailScale = d3.scaleSqrt().range([1.5, 8]);

    this.tooltip = tooltip();

    this.g = this.svg.append("g").attr("class", "map-layers");
    this.countryLayer = this.g.append("g").attr("class", "country-layer");
    this.aggregateLayer = this.g.append("g").attr("class", "aggregate-layer");
    this.detailLayer = this.g.append("g").attr("class", "detail-layer");

    this.drawBasemap();
    this.setupZoom();
  }

  drawBasemap() {
    this.countryLayer
      .selectAll("path")
      .data(this.world.features)
      .join("path")
      .attr("d", this.geoPath)
      .attr("fill", "#e5e7eb")
      .attr("stroke", "#fff")
      .attr("stroke-width", 0.6);
  }

  setupZoom() {
    const zoomed = (event) => {
      this.currentZoom = event.transform.k;
      this.g.attr("transform", event.transform);
      this.aggregateLayer
        .selectAll("circle")
        .attr("r", (d) => this.radiusScale(d.total) / this.currentZoom);
      this.detailLayer
        .selectAll("circle")
        .attr("r", (d) => this.detailScale(d.capacity) / Math.sqrt(this.currentZoom));
      this.updateSemanticVisibility();
    };

    this.svg.call(
      d3
        .zoom()
        .scaleExtent([1, 12])
        .on("zoom", zoomed)
    );
  }

  updateSemanticVisibility() {
    const showDetail = this.currentZoom >= DETAIL_THRESHOLD;
    this.aggregateLayer.attr("opacity", showDetail ? 0 : 1);
    this.detailLayer.attr("opacity", showDetail ? 1 : 0);
  }

  update(plants) {
    // Normalize incoming plant objects to expected fields and log for debugging
    const normalized = (plants || []).map((p, i) => {
      const countryCode =
        p.countryCode ??
        p.country_code ??
        p.iso_a3 ??
        p.iso3 ??
        p.iso ??
        p.country ??
        p.country_name ??
        null;

      const id = p.id ?? p.plant_id ?? p.plantId ?? `${p.latitude}_${p.longitude}_${i}`;

      const capacity = +(
        p.capacity ??
        p.capacity_mw ??
        p.capacityMW ??
        p.cap ??
        0
      );

      let latitude = p.latitude ?? p.lat ?? p.Lat ?? p.Latitude ?? null;
      let longitude = p.longitude ?? p.lon ?? p.lng ?? p.long ?? p.Longitude ?? null;

      latitude = latitude == null ? null : +latitude;
      longitude = longitude == null ? null : +longitude;

      // Fix common lat/long swap when values are clearly out of range
      if (
        latitude != null &&
        longitude != null &&
        Math.abs(latitude) > 90 &&
        Math.abs(longitude) <= 90
      ) {
        [latitude, longitude] = [longitude, latitude];
      }

      return {
        ...p,
        id,
        capacity,
        latitude,
        longitude,
        countryCode,
      };
    });

    console.log("PowerMap.update: received", plants?.length ?? 0, "-> normalized", normalized.length);
    console.log("PowerMap.update: sample normalized[0]", normalized[0]);
    const missingCoords = normalized.filter((d) => d.latitude == null || d.longitude == null);
    if (missingCoords.length) console.warn("PowerMap.update: plants with missing coords:", missingCoords.slice(0, 6));
    const missingCountry = normalized.filter((d) => !d.countryCode);
    if (missingCountry.length) console.warn("PowerMap.update: plants with missing countryCode:", missingCountry.slice(0, 6));
    console.log("PowerMap.update: countryCentroids keys (sample):", Array.from(this.countryCentroids.keys()).slice(0, 12));

    this.filteredPlants = normalized;
    this.updateAggregates();
    this.updateDetails();
  }
  updateAggregates() {
    // Sum capacities by country
    const totals = d3.rollups(
      this.filteredPlants,
      (values) => d3.sum(values, (d) => d.capacity),
      (d) => d.countryCode
    );

    this.radiusScale.domain([0, d3.max(totals, (d) => d[1]) || 1]);

    const nodes = totals.map(([countryCode, total]) => {
      if (!countryCode) return null;

      let centroid = this.countryCentroids.get(countryCode);
      if (!centroid && typeof countryCode === "string") {
        centroid = this.countryCentroids.get(countryCode.toUpperCase());
      }

      // Check missing centroid
      if (!centroid || !Array.isArray(centroid) || centroid.length !== 2) {
        console.warn("Missing or invalid centroid for", countryCode, centroid);
        return null;
      }

      const [lon, lat] = centroid;

      // Check numeric values
      if (!Number.isFinite(lat) || !Number.isFinite(lon)) {
        console.warn(" Non-numeric centroid for", countryCode, centroid);
        return null;
      }

      // Project lat/lon to x/y pixels
      const [x, y] = this.projection([lon, lat]);

      if (!Number.isFinite(x) || !Number.isFinite(y)) {
        console.warn(" Projection failed for", countryCode, centroid);
        return null;
      }

      return { countryCode, total, x, y };
    });

    const filteredNodes = nodes.filter(Boolean);

    // Bind data to aggregate circles
    const circles = this.aggregateLayer
      .selectAll("circle")
      .data(filteredNodes, (d) => d.countryCode);

    circles
      .join(
        (enter) =>
          enter
            .append("circle")
            .attr("cx", (d) => d.x)
            .attr("cy", (d) => d.y)
            .attr("r", 0)
            .attr("fill", "rgba(14,116,144,0.75)")
            .attr("stroke", "#0f172a")
            .attr("stroke-width", 0.5)
            .call((enterSel) =>
              enterSel.transition().duration(400)
                .attr("r", (d) => this.radiusScale(d.total) / this.currentZoom)
            ),
        (update) =>
          update.call((updateSel) =>
            updateSel.transition().duration(250)
              .attr("cx", (d) => d.x)
              .attr("cy", (d) => d.y)
              .attr("r", (d) => this.radiusScale(d.total) / this.currentZoom)
          ),
        (exit) => exit.transition().duration(200).attr("r", 0).remove()
      )
      .on("mouseenter", (event, d) => {
        this.tooltip.show(
          `<strong>${d.countryCode}</strong><br/>Capacity: ${formatMW(d.total)}`,
          event
        );
      })
      .on("mousemove", (event) => this.tooltip.move(event))
      .on("mouseleave", () => this.tooltip.hide());
  }





  updateDetails() {
    // Filter out plants without valid numeric coordinates before projecting
    const validPlants = this.filteredPlants.filter((d) => {
      const lat = d.latitude;
      const lon = d.longitude;
      return (
        lat != null &&
        lon != null &&
        Number.isFinite(lat) &&
        Number.isFinite(lon) &&
        Math.abs(lat) <= 90 &&
        Math.abs(lon) <= 180
      );
    });

    const extent = d3.extent(validPlants, (d) => d.capacity);
    this.detailScale.domain([0, extent[1] || 1]);

    const circles = this.detailLayer.selectAll("circle").data(validPlants, (d) => d.id);

    circles
      .join(
        (enter) =>
          enter
            .append("circle")
            .attr("cx", (d) => this.projection([d.longitude, d.latitude])[0])
            .attr("cy", (d) => this.projection([d.longitude, d.latitude])[1])
            .attr("fill", (d) => fuelColorScale(d.primaryFuel))
            .attr("stroke", "#0f172a")
            .attr("stroke-width", 0.4)
            .attr("r", 0)
            .attr("opacity", 0.85)
            .call((enterSel) =>
              enterSel
                .transition()
                .duration(250)
                .attr("r", (d) => this.detailScale(d.capacity) / Math.sqrt(this.currentZoom))
            ),
        (update) =>
          update.call((updateSel) =>
            updateSel
              .transition()
              .duration(150)
              .attr("cx", (d) => this.projection([d.longitude, d.latitude])[0])
              .attr("cy", (d) => this.projection([d.longitude, d.latitude])[1])
              .attr("r", (d) => this.detailScale(d.capacity) / Math.sqrt(this.currentZoom))
              .attr("fill", (d) => fuelColorScale(d.primaryFuel))
          ),
        (exit) => exit.transition().duration(200).attr("r", 0).remove()
      )
      .on("mouseenter", (event, d) => {
        this.tooltip.show(
          `<strong>${d.name}</strong><br/>
          ${d.countryName}<br/>
          Fuel: ${d.primaryFuel}<br/>
          Capacity: ${formatMW(d.capacity)}<br/>
          Commissioned: ${d.commissioningYear ?? "Unknown"}`,
          event
        );
      })
      .on("mousemove", (event) => this.tooltip.move(event))
      .on("mouseleave", () => this.tooltip.hide());

    this.updateSemanticVisibility();
  }
}