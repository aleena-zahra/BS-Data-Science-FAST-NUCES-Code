import { responsivefy, tooltip } from "../utils/helpers.js";

const WIDTH = 700;
const HEIGHT = 420;

export class LifeMap {
  constructor({ el, world }) {
    this.root = d3.select(el);
    this.world = world;
    this.svg = this.root.append("svg").attr("class", "life-map");
    responsivefy(this.svg, WIDTH, HEIGHT);

    this.projection = d3.geoMercator().fitSize([WIDTH, HEIGHT], world);
    this.path = d3.geoPath(this.projection);
    this.tooltip = tooltip();

    this.color = d3.scaleSequential(d3.interpolateOrRd).domain([80, 85]);

    this.svg
      .append("g")
      .attr("class", "countries")
      .selectAll("path")
      .data(world.features)
      .join("path")
      .attr("d", this.path)
      .attr("fill", "#393939ff")
      .attr("stroke", "#fff")
      .attr("stroke-width", 0.5);
  }

  update(yearRows) {
    const lifeByIso = new Map(yearRows.map((d) => [d.iso, d]));
    const lifeValues = yearRows.map((d) => d.life);
    this.color.domain([d3.min(lifeValues) || 40, d3.max(lifeValues) || 85]);

    this.svg
      .select(".countries")
      .selectAll("path")
      .attr("fill", (feature) => {
        const record = lifeByIso.get(feature.id);
        return record ? this.color(record.life) : "#8eb4ffff";
      })
      .on("mouseenter", (event, feature) => {
        const record = lifeByIso.get(feature.id);
        if (!record) return;
        this.tooltip.show(
          `<strong>${record.name}</strong><br/>Life Expectancy: ${record.life.toFixed(1)} yrs`,
          event
        );
      })
      .on("mousemove", (event) => this.tooltip.move(event))
      .on("mouseleave", () => this.tooltip.hide());
  }
}

