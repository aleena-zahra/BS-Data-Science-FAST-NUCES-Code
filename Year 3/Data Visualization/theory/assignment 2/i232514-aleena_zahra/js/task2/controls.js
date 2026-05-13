const SLIDER_WIDTH = 600;
const SLIDER_HEIGHT = 60;

export class PlaybackControls {
  constructor({ buttonEl, sliderEl, yearLabelEl, years, onYearChange, onToggle }) {
    this.button = d3.select(buttonEl);
    this.yearLabel = d3.select(yearLabelEl);
    this.onYearChange = onYearChange;
    this.onToggle = onToggle;
    this.years = years;
    this.playing = false;

    this.button.on("click", () => this.toggle());

    this.scale = d3.scaleLinear().domain(d3.extent(years)).range([10, SLIDER_WIDTH - 10]);

    this.svg = d3
      .select(sliderEl)
      .append("svg")
      .attr("width", "100%")
      .attr("height", SLIDER_HEIGHT)
      .attr("viewBox", `0 0 ${SLIDER_WIDTH} ${SLIDER_HEIGHT}`);

    this.track = this.svg
      .append("line")
      .attr("x1", 10)
      .attr("x2", SLIDER_WIDTH - 10)
      .attr("y1", SLIDER_HEIGHT / 2)
      .attr("y2", SLIDER_HEIGHT / 2)
      .attr("stroke", "#cbd5f5")
      .attr("stroke-width", 6)
      .attr("stroke-linecap", "round");

    this.handle = this.svg
      .append("circle")
      .attr("r", 10)
      .attr("cy", SLIDER_HEIGHT / 2)
      .attr("fill", "#0b3d91")
      .attr("stroke", "#fff")
      .attr("stroke-width", 2)
      .style("cursor", "grab");

    this.svg.call(
      d3
        .drag()
        .on("start drag", (event) => this.onDrag(event))
        .on("end", () => (this.handle.style("cursor", "grab")))
    );
  }

  onDrag(event) {
    const x = Math.max(10, Math.min(SLIDER_WIDTH - 10, event.x));
    const year = Math.round(this.scale.invert(x));
    const clampedYear = Math.max(this.years[0], Math.min(this.years[this.years.length - 1], year));
    this.setYear(clampedYear);
    this.onYearChange(clampedYear, true);
  }

  setYear(year) {
    this.currentYear = year;
    this.handle.attr("cx", this.scale(year));
    this.yearLabel.text(`Year: ${year}`);
  }

  toggle(forceState) {
    if (typeof forceState === "boolean") {
      this.playing = forceState;
    } else {
      this.playing = !this.playing;
    }
    this.button.text(this.playing ? "Pause" : "Play");
    this.onToggle(this.playing);
  }
}

