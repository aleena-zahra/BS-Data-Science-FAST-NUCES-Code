import { fuelColorScale, responsivefy } from "../utils/helpers.js";

const MARGIN = { top: 10, right: 20, bottom: 30, left: 40 };
const WIDTH = 900;
const HEIGHT = 220;

export class CapacityTimeline {
  constructor({ el, onBrush }) {
    this.root = d3.select(el);
    this.onBrush = onBrush;
    this.categories = [];
    this.x = d3.scaleLinear();
    this.y = d3.scaleLinear();

    this.svg = this.root.append("svg").attr("class", "capacity-timeline");
    responsivefy(this.svg, WIDTH, HEIGHT);

    this.chartWidth = WIDTH - MARGIN.left - MARGIN.right;
    this.chartHeight = HEIGHT - MARGIN.top - MARGIN.bottom;

    this.container = this.svg.append("g").attr("transform", `translate(${MARGIN.left},${MARGIN.top})`);
    this.areaGroup = this.container.append("g").attr("class", "areas");
    this.xAxisGroup = this.container
      .append("g")
      .attr("class", "x-axis")
      .attr("transform", `translate(0, ${this.chartHeight})`);
    this.yAxisGroup = this.container.append("g").attr("class", "y-axis");

    this.brush = d3
      .brushX()
      .extent([
        [0, 0],
        [this.chartWidth, this.chartHeight],
      ])
      .on("brush end", (event) => this.handleBrush(event));

    this.container.append("g").attr("class", "brush").call(this.brush);
  }

  setData(plants) {
    const data = plants.filter((d) => Number.isFinite(d.commissioningYear));
    const totalsByFuel = d3.rollups(
      data,
      (values) => d3.sum(values, (d) => d.capacity),
      (d) => d.primaryFuel
    );
    const sorted = totalsByFuel.sort((a, b) => d3.descending(a[1], b[1]));
    this.categories = sorted.slice(0, 6).map(([fuel]) => fuel);
    if (!this.categories.includes("Other")) {
      this.categories.push("Other");
    }
    fuelColorScale.domain(this.categories);

    const nested = d3.rollups(
      data,
      (values) =>
        d3.rollups(
          values,
          (fuelGroup) => d3.sum(fuelGroup, (d) => d.capacity),
          (d) => (this.categories.includes(d.primaryFuel) ? d.primaryFuel : "Other")
        ),
      (d) => d.commissioningYear
    );

    const years = Array.from(new Set(nested.map(([year]) => year))).sort((a, b) => a - b);
    this.series = years.map((year) => {
      const entry = { year };
      this.categories.forEach((cat) => {
        entry[cat] = 0;
      });
      const fuelTotals = nested.find(([y]) => y === year)?.[1] ?? [];
      fuelTotals.forEach(([fuel, total]) => {
        entry[fuel] = total;
      });
      return entry;
    });

    this.draw();
  }

  draw() {
    if (!this.series?.length) return;
    const yearExtent = d3.extent(this.series, (d) => d.year);
    this.x.domain(yearExtent).range([0, this.chartWidth]);
    this.y
      .domain([0, d3.max(this.series, (d) => d3.sum(this.categories, (key) => d[key]))])
      .range([this.chartHeight, 0])
      .nice();

    const stack = d3.stack().keys(this.categories);
    const stacked = stack(this.series);

    const area = d3
      .area()
      .x((d) => this.x(d.data.year))
      .y0((d) => this.y(d[0]))
      .y1((d) => this.y(d[1]))
      .curve(d3.curveMonotoneX);

    this.areaGroup
      .selectAll("path")
      .data(stacked, (d) => d.key)
      .join("path")
      .attr("fill", (d) => fuelColorScale(d.key))
      .attr("opacity", 0.85)
      .transition()
      .duration(400)
      .attr("d", area);

    const xAxis = d3.axisBottom(this.x).ticks(6).tickFormat(d3.format("d"));
    const yAxis = d3.axisLeft(this.y).ticks(4).tickFormat((d) => `${d3.format(".2s")(d)} MW`);
    this.xAxisGroup.transition().call(xAxis);
    this.yAxisGroup.transition().call(yAxis);
  }

  handleBrush(event) {
    if (!event.selection) {
      this.onBrush(this.x.domain());
      return;
    }
    const [x0, x1] = event.selection.map(this.x.invert);
    this.onBrush([Math.floor(x0), Math.ceil(x1)]);
  }
}

