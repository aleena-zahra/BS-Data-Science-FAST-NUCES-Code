import { continentColorScale, formatGDP, formatPopulation, responsivefy, tooltip } from "../utils/helpers.js";

const MARGIN = { top: 20, right: 30, bottom: 40, left: 60 };
const WIDTH = 720;
const HEIGHT = 480;

export class MotionChart {
  constructor({ el }) {
    this.root = d3.select(el);
    this.svg = this.root.append("svg").attr("class", "motion-chart");
    responsivefy(this.svg, WIDTH, HEIGHT);

    this.chartWidth = WIDTH - MARGIN.left - MARGIN.right;
    this.chartHeight = HEIGHT - MARGIN.top - MARGIN.bottom;

    this.g = this.svg.append("g").attr("transform", `translate(${MARGIN.left},${MARGIN.top})`);
    this.x = d3.scaleLog().clamp(true);
    this.y = d3.scaleLinear();
    this.r = d3.scaleSqrt();

    this.tooltip = tooltip();

    this.xAxis = this.g.append("g").attr("transform", `translate(0,${this.chartHeight})`);
    this.yAxis = this.g.append("g");
    this.pointsGroup = this.g.append("g").attr("class", "points");

    this.xLabel = this.g
      .append("text")
      .attr("class", "axis-label")
      .attr("x", this.chartWidth)
      .attr("y", this.chartHeight + 32)
      .attr("text-anchor", "end")
      .text("GDP per Capita (log)");

    this.yLabel = this.g
      .append("text")
      .attr("class", "axis-label")
      .attr("x", -40)
      .attr("y", -10)
      .text("Life Expectancy");
  }

  setDomains({ rowsByYear }) {
    const allRows = Array.from(rowsByYear.values()).flat();
    this.x.domain(d3.extent(allRows, (d) => Math.max(d.gdp, 1))).range([0, this.chartWidth]);
    this.y.domain([d3.min(allRows, (d) => d.life) - 5, d3.max(allRows, (d) => d.life) + 5]).range([this.chartHeight, 0]);
    this.r.domain(d3.extent(allRows, (d) => d.pop)).range([4, 35]);

    this.xAxis.call(d3.axisBottom(this.x).ticks(6, "~s"));
    this.yAxis.call(d3.axisLeft(this.y));
  }

  update(yearRows, year) {
    this.currentYear = year;
    const circles = this.pointsGroup.selectAll("circle").data(yearRows, (d) => d.iso);

    circles
      .join(
        (enter) =>
          enter
            .append("circle")
            .attr("cx", (d) => this.x(Math.max(d.gdp, 1)))
            .attr("cy", (d) => this.y(d.life))
            .attr("fill", (d) => continentColorScale(d.continent))
            .attr("stroke", "#0f172a")
            .attr("stroke-width", 0.6)
            .attr("r", 0)
            .attr("opacity", 0.9)
            .call((enterSel) =>
              enterSel.transition().duration(600).attr("r", (d) => this.r(d.pop))
            ),
        (update) =>
          update.call((updateSel) =>
            updateSel
              .transition()
              .duration(600)
              .ease(d3.easeCubicOut)
              .attr("cx", (d) => this.x(Math.max(d.gdp, 1)))
              .attr("cy", (d) => this.y(d.life))
              .attr("r", (d) => this.r(d.pop))
              .attr("fill", (d) => continentColorScale(d.continent))
          ),
        (exit) => exit.transition().duration(200).attr("r", 0).remove()
      )
      .on("mouseenter", (event, d) => {
        this.tooltip.show(
          `<strong>${d.name}</strong><br/>${d.continent}<br/>${formatGDP(d.gdp)}<br/>Life Exp.: ${d.life.toFixed(
            1
          )} years<br/>${formatPopulation(d.pop)}`,
          event
        );
      })
      .on("mousemove", (event) => this.tooltip.move(event))
      .on("mouseleave", () => this.tooltip.hide());
  }

  highlightContinent(continent) {
    this.pointsGroup
      .selectAll("circle")
      .attr("opacity", (d) => {
        if (!continent) return 0.9;
        return d.continent === continent ? 1 : 0.15;
      })
      .attr("stroke-width", (d) => (continent && d.continent === continent ? 1.4 : 0.6));
  }
}

