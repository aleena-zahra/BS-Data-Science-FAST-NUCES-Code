import { continentColorScale, responsivefy, tooltip } from "../utils/helpers.js";

const WIDTH = 520;
const HEIGHT = 380;
const RADIUS = Math.min(WIDTH, HEIGHT) / 2;

export class HierarchyChart {
  constructor({ el, onHover }) {
    this.root = d3.select(el);
    this.onHover = onHover;
    this.svg = this.root.append("svg").attr("class", "hierarchy-chart");
    responsivefy(this.svg, WIDTH, HEIGHT);

    this.g = this.svg.append("g").attr("transform", `translate(${WIDTH / 2}, ${HEIGHT / 2})`);
    this.partition = d3.partition().size([2 * Math.PI, RADIUS]);
    this.arc = d3
      .arc()
      .startAngle((d) => d.x0)
      .endAngle((d) => d.x1)
      .innerRadius((d) => d.y0)
      .outerRadius((d) => d.y1);

    this.tooltip = tooltip();
  }

  update(rows) {
    const continents = d3.rollups(
      rows,
      (values) =>
        d3.rollups(
          values,
          (countries) => d3.sum(countries, (d) => d.pop),
          (d) => d.name
        ),
      (d) => d.continent
    );

    const children = continents.map(([continent, countries]) => ({
      name: continent,
      value: d3.sum(countries, (d) => d[1]),
      children: countries.map(([country, value]) => ({ name: country, value })),
    }));

    const root = this.partition(
      d3
        .hierarchy({ name: "World", children })
        .sum((d) => d.value)
        .sort((a, b) => b.value - a.value)
    );

    const nodes = root.descendants().filter((d) => d.depth > 0);

    const arcs = this.g.selectAll("path").data(nodes, (d) => d.data.name);

    arcs
      .join(
        (enter) =>
          enter
            .append("path")
            .attr("d", this.arc)
            .attr("fill", (d) => (d.depth === 1 ? continentColorScale(d.data.name) : "#94a3b8"))
            .attr("stroke", "#fff")
            .attr("stroke-width", 1)
            .attr("opacity", (d) => (d.depth === 1 ? 0.95 : 0.5)),
        (update) => update.attr("d", this.arc)
      )
      .on("mouseenter", (event, d) => {
        const percent = ((d.value / root.value) * 100).toFixed(2);
        this.tooltip.show(
          `<strong>${d.data.name}</strong><br/>Share: ${percent}%`,
          event
        );
        if (d.depth === 1) {
          this.onHover(d.data.name);
        }
      })
      .on("mousemove", (event) => this.tooltip.move(event))
      .on("mouseleave", () => {
        this.tooltip.hide();
        this.onHover(null);
      });
  }
}

