import { fuelColorScale, formatMW, responsivefy, tooltip } from "../utils/helpers.js";

const WIDTH = 420;
const HEIGHT = 420;

export class FuelForce {
  constructor({ el, onSelect }) {
    this.root = d3.select(el);
    this.onSelect = onSelect;
    this.activeFuel = null;

    this.svg = this.root.append("svg").attr("class", "fuel-force");
    responsivefy(this.svg, WIDTH, HEIGHT);

    this.g = this.svg.append("g").attr("transform", `translate(${WIDTH / 2}, ${HEIGHT / 2})`);
    this.nodes = [];
    this.tooltip = tooltip();

    this.radiusScale = d3.scaleSqrt().range([15, 70]);

    this.simulation = d3
      .forceSimulation()
      .force("charge", d3.forceManyBody().strength(5))
      .force("collide", d3.forceCollide((d) => d.radius + 4))
      .force("center", d3.forceCenter(0, 0))
      .force("y", d3.forceY().strength(0.03))
      .force("x", d3.forceX().strength(0.03));
  }

  update(plants) {
    const totals = d3.rollups(
      plants,
      (values) => ({
        total: d3.sum(values, (d) => d.capacity),
        count: values.length,
      }),
      (d) => d.primaryFuel
    );

    this.radiusScale.domain([0, d3.max(totals, (d) => d[1].total) || 1]);

    this.nodes = totals.map(([fuel, summary]) => ({
      fuel,
      total: summary.total,
      count: summary.count,
      radius: this.radiusScale(summary.total),
    }));

    this.draw();
  }

  draw() {
    const circles = this.g.selectAll("g.node").data(this.nodes, (d) => d.fuel);

    const nodeEnter = circles
      .join((enter) => {
        const node = enter.append("g").attr("class", "node").style("cursor", "pointer");
        node
          .append("circle")
          .attr("r", 0)
          .attr("fill", (d) => fuelColorScale(d.fuel))
          .attr("stroke", "#0f172a")
          .attr("stroke-width", 1);

        node
          .append("text")
          .attr("text-anchor", "middle")
          .attr("dy", "0.35em")
          .attr("fill", "#0f172a")
          .attr("font-size", "12px")
          .text((d) => d.fuel);

        return node;
      })
      .on("mouseenter", (event, d) => {
        this.tooltip.show(
          `<strong>${d.fuel}</strong><br/>Plants: ${d.count}<br/>Capacity: ${formatMW(d.total)}`,
          event
        );
      })
      .on("mousemove", (event) => this.tooltip.move(event))
      .on("mouseleave", () => this.tooltip.hide())
      .on("click", (_, d) => {
        this.activeFuel = this.activeFuel === d.fuel ? null : d.fuel;
        this.highlightActive();
        this.onSelect(this.activeFuel);
      });

    nodeEnter
      .select("circle")
      .transition()
      .duration(300)
      .attr("r", (d) => d.radius);

    this.simulation.nodes(this.nodes).on("tick", () => {
      nodeEnter.attr("transform", (d) => `translate(${d.x},${d.y})`);
    });

    this.highlightActive();
  }

  highlightActive() {
    this.g.selectAll("circle").attr("opacity", (d) => (this.activeFuel && d.fuel !== this.activeFuel ? 0.25 : 0.95));
  }
}

