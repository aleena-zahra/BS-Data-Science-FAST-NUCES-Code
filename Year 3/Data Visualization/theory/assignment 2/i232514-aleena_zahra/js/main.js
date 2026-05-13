import { loadTask1Data, loadTask2Data } from "./utils/dataLoader.js";
import { Task1Controller } from "./task1/controller.js";
import { MotionChart } from "./task2/motionChart.js";
import { LifeMap } from "./task2/choropleth.js";
import { HierarchyChart } from "./task2/hierarchy.js";
import { PlaybackControls } from "./task2/controls.js";
import { continentColorScale } from "./utils/helpers.js";

const state = {
  task2: {
    yearIndex: 0,
    timer: null,
  },
};

const select = (selector) => document.querySelector(selector);

async function bootstrap() {
  const [task1Data, task2Data] = await Promise.all([loadTask1Data(), loadTask2Data()]);

  new Task1Controller({
    mapEl: "#task1-map",
    legendEl: "#task1-map-legend",
    bubblesEl: "#task1-bubbles",
    timelineEl: "#task1-timeline",
    data: task1Data,
  });

  initTask2(task2Data);
}

function initTask2(data) {
  const motionChart = new MotionChart({ el: "#motion-chart" });
  const lifeMap = new LifeMap({ el: "#task2-map", world: data.world });
  const hierarchy = new HierarchyChart({
    el: "#hierarchy-chart",
    onHover: (continent) => motionChart.highlightContinent(continent),
  });

  motionChart.setDomains(data);
  continentColorScale.domain(data.continents);
  drawMotionLegend(data.continents);

  const controls = new PlaybackControls({
    buttonEl: "#play-pause",
    sliderEl: "#year-slider",
    yearLabelEl: "#current-year",
    years: data.years,
    onYearChange: (year, userAction = false) => {
      setYear(data, motionChart, lifeMap, hierarchy, year);
      if (userAction) {
        controls.toggle(false);
        stopTimer();
      }
    },
    onToggle: (playing) => {
      if (playing) {
        startTimer(data, motionChart, lifeMap, hierarchy, controls);
      } else {
        stopTimer();
      }
    },
  });

  const initialYear = data.years[0];
  controls.setYear(initialYear);
  setYear(data, motionChart, lifeMap, hierarchy, initialYear);
}

function drawMotionLegend(continents) {
  const legend = d3.select("#motion-legend");
  legend.selectAll("*").remove();
  const items = legend.selectAll("span").data(continents).join("span");
  items.html(
    (continent) =>
      `<span class="swatch" style="background:${continentColorScale(continent)}"></span>${continent}`
  );
}

function setYear(data, motionChart, lifeMap, hierarchy, year) {
  const rows = data.rowsByYear.get(year) ?? [];
  motionChart.update(rows, year);
  lifeMap.update(rows);
  hierarchy.update(rows);
  state.task2.yearIndex = data.years.indexOf(year);
}

function startTimer(data, motionChart, lifeMap, hierarchy, controls) {
  stopTimer();
  state.task2.timer = d3.interval(() => {
    state.task2.yearIndex = (state.task2.yearIndex + 1) % data.years.length;
    const year = data.years[state.task2.yearIndex];
    controls.setYear(year);
    setYear(data, motionChart, lifeMap, hierarchy, year);
    if (state.task2.yearIndex === data.years.length - 1) {
      controls.toggle(false);
      stopTimer();
    }
  }, 1500);
}

function stopTimer() {
  if (state.task2.timer) {
    state.task2.timer.stop();
    state.task2.timer = null;
  }
}

bootstrap();

