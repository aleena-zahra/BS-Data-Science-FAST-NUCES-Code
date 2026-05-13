export const formatCapacity = d3.format(",.0f");
export const formatMW = (value) => `${formatCapacity(value)} MW`;
export const formatPopulation = (value) =>
  `${d3.format(".2s")(value).replace("G", "B")} people`;
export const formatGDP = (value) => `$${d3.format(".2s")(value)}/capita`;

export const fuelColorScale = d3.scaleOrdinal().range([
  "#2c7bb6",
  "#abd9e9",
  "#fdae61",
  "#d7191c",
  "#7b3294",
  "#1a9641",
  "#f46d43",
  "#fee08b",
  "#4575b4",
  "#a6d96a",
  "#66bd63",
  "#fdae61",
]);

export const continentColorScale = d3.scaleOrdinal(d3.schemeTableau10);

export const responsivefy = (svg, width, height) => {
  svg.attr("viewBox", `0 0 ${width} ${height}`).attr("preserveAspectRatio", "xMidYMid meet");
};

export const debounce = (fn, wait = 150) => {
  let timeout;
  return (...args) => {
    clearTimeout(timeout);
    timeout = setTimeout(() => fn(...args), wait);
  };
};

export const tooltip = () => {
  const div = d3
    .select("body")
    .append("div")
    .attr("class", "tooltip")
    .style("position", "absolute")
    .style("pointer-events", "none")
    .style("background", "rgba(15,23,42,0.9)")
    .style("color", "#fff")
    .style("padding", "8px 12px")
    .style("border-radius", "6px")
    .style("font-size", "0.85rem")
    .style("opacity", 0);

  const show = (html, event) => {
    div
      .html(html)
      .style("opacity", 1)
      .style("left", `${event.pageX + 12}px`)
      .style("top", `${event.pageY - 28}px`);
  };

  const move = (event) => {
    div.style("left", `${event.pageX + 12}px`).style("top", `${event.pageY - 28}px`);
  };

  const hide = () => {
    div.style("opacity", 0);
  };

  return { show, move, hide };
};

