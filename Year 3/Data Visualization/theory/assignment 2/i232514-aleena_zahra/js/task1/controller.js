import { PowerMap } from "./map.js";
import { FuelForce } from "./bubbles.js";
import { CapacityTimeline } from "./timeline.js";

export class Task1Controller {
  constructor({ mapEl, legendEl, bubblesEl, timelineEl, data }) {
    this.data = data;
    this.map = new PowerMap({
      el: mapEl,
      world: data.world,
      countryCentroids: data.countryCentroids,
    });
    this.bubbles = new FuelForce({
      el: bubblesEl,
      onSelect: (fuel) => this.handleFuelSelect(fuel),
    });
    this.timeline = new CapacityTimeline({
      el: timelineEl,
      onBrush: (range) => this.handleBrush(range),
    });

    this.legendEl = legendEl;
    this.filters = {
      fuel: null,
      years: this.computeYearExtent(),
    };

    this.timeline.setData(this.data.plants);
    this.update();
  }

  computeYearExtent() {
    return d3.extent(
      this.data.plants
        .filter((d) => Number.isFinite(d.commissioningYear))
        .map((d) => d.commissioningYear)
    );
  }

  handleFuelSelect(fuel) {
    this.filters.fuel = fuel;
    this.update();
  }

  handleBrush(range) {
    this.filters.years = range;
    this.update();
  }

  update() {
    const [minYear, maxYear] = this.filters.years;
    const yearFiltered = this.data.plants.filter((d) => {
      if (!Number.isFinite(d.commissioningYear)) return true;
      return d.commissioningYear >= minYear && d.commissioningYear <= maxYear;
    });

    const fuelFiltered = yearFiltered.filter((d) =>
      this.filters.fuel ? d.primaryFuel === this.filters.fuel : true
    );

    this.map.update(fuelFiltered);
    this.bubbles.update(yearFiltered);
    this.updateLegend(yearFiltered);
  }

  updateLegend(plants) {
    const legend = d3.select(this.legendEl);
    legend.selectAll("*").remove();
    const totalCapacity = d3.sum(plants, (d) => d.capacity);
    const totalPlants = plants.length;
    legend
      .append("span")
      .html(`<strong>Plants:</strong> ${d3.format(",")(totalPlants)}`);
    legend
      .append("span")
      .html(`<strong>Capacity:</strong> ${d3.format(".2s")(totalCapacity)} MW`);
  }
}

