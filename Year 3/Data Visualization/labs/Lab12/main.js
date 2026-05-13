import * as d3 from "https://cdn.jsdelivr.net/npm/d3@7/dist/d3.min.js";

const statusEl = document.getElementById("status");
const tooltipEl = document.getElementById("q-tooltip");
const summary = { Q1: null, Q2: null, Q3: null, Q4: null };

function appendStatus(msg) {
  console.log(msg);
  statusEl.textContent += "\n" + msg;
}



async function initQ1() {
  const checks = {
    csvLoaded: false,
    threeLines: false,
    brushSync: false,
    zoomSync: false,
    legendToggle: false,
    tooltip: false,
  };
  try {
    const parseDate = d3.timeParse("%Y-%m-%d");
    const data = await d3.csv("data/weather.csv", d => {
      const row = {
        date: parseDate(d.date || d.Date || d.time || d.timestamp),
        temperature: +d.temperature || +d.temp,
        humidity: +d.humidity || +d.hum,
        wind: +d.wind || +d.windSpeed || +d.wind_speed,
      };
      if (!checks.csvLoaded) {
        console.log("Q1 parsed row example:", row, d);
        checks.csvLoaded = true;
      }
      return row;
    });
    const filtered = data.filter(
      d =>
        d.date &&
        !Number.isNaN(d.temperature) &&
        !Number.isNaN(d.humidity) &&
        !Number.isNaN(d.wind)
    );

    const svg = d3.select("#q1-svg");
    svg.selectAll("*").remove();
    const width = +svg.attr("width");
    const height = +svg.attr("height");
    const margin = { top: 20, right: 80, bottom: 110, left: 50 };
    const marginBrush = { top: height - 90, right: 80, bottom: 20, left: 50 };
    const innerHeight = height - margin.top - margin.bottom;
    const brushHeight = height - marginBrush.top - marginBrush.bottom;

    const x = d3.scaleTime().range([0, width - margin.left - margin.right]);
    const xBrush = d3.scaleTime().range([0, width - margin.left - margin.right]);
    const y = d3.scaleLinear().range([innerHeight, 0]);
    const color = d3
      .scaleOrdinal(d3.schemeCategory10)
      .domain(["temperature", "humidity", "wind"]);

    const series = [
      { key: "temperature", name: "Temperature" },
      { key: "humidity", name: "Humidity" },
      { key: "wind", name: "Wind" },
    ];
    const visible = { temperature: true, humidity: true, wind: true };

    x.domain(d3.extent(filtered, d => d.date));
    xBrush.domain(x.domain());

    const yExtent = [
      d3.min(series, s => d3.min(filtered, d => d[s.key])),
      d3.max(series, s => d3.max(filtered, d => d[s.key])),
    ];
    y.domain(yExtent).nice();

    const mainG = svg
      .append("g")
      .attr("transform", `translate(${margin.left},${margin.top})`);
    const brushG = svg
      .append("g")
      .attr("transform", `translate(${marginBrush.left},${marginBrush.top})`);

    const xAxis = d3.axisBottom(x);
    const yAxis = d3.axisLeft(y);
    const xAxisBrush = d3.axisBottom(xBrush);

    mainG
      .append("g")
      .attr("class", "x-axis")
      .attr("transform", `translate(0,${innerHeight})`)
      .call(xAxis);
    mainG.append("g").attr("class", "y-axis").call(yAxis);

    mainG
      .append("g")
      .attr("class", "grid")
      .call(
        d3.axisLeft(y).tickSize(-(width - margin.left - margin.right)).tickFormat("")
      );

    brushG
      .append("g")
      .attr("class", "x-axis-brush")
      .attr("transform", `translate(0,${brushHeight})`)
      .call(xAxisBrush);

    const lineGen = (key, scaleX) =>
      d3
        .line()
        .x(d => scaleX(d.date))
        .y(d => y(d[key]));

    const linesG = mainG.append("g").attr("class", "lines");
    const lines = {};
    series.forEach(s => {
      lines[s.key] = linesG
        .append("path")
        .datum(filtered)
        .attr("fill", "none")
        .attr("stroke", color(s.key))
        .attr("stroke-width", 1.5)
        .attr("class", `line-${s.key}`)
        .attr("d", lineGen(s.key, x));
    });

    checks.threeLines = Object.keys(lines).length === 3;

    const brushLinesG = brushG.append("g").attr("class", "brush-lines");
    const brushLines = {};
    series.forEach(s => {
      brushLines[s.key] = brushLinesG
        .append("path")
        .datum(filtered)
        .attr("fill", "none")
        .attr("stroke", color(s.key))
        .attr("stroke-width", 1)
        .attr("d", lineGen(s.key, xBrush));
    });

    const brush = d3
      .brushX()
      .extent([[0, 0], [width - margin.left - margin.right, brushHeight]])
      .on("brush end", brushed);

    const defaultSelection = [xBrush.domain()[0], xBrush.domain()[1]];
    brushG
      .append("g")
      .attr("class", "x-brush")
      .call(brush)
      .call(g => g.call(brush.move, defaultSelection.map(xBrush)));

    const zoom = d3
      .zoom()
      .scaleExtent([1, 20])
      .translateExtent([[0, 0], [width - margin.left - margin.right, innerHeight]])
      .extent([[0, 0], [width - margin.left - margin.right, innerHeight]])
      .on("zoom", zoomed);

    svg.call(zoom).on("dblclick.zoom", null);

    function brushed({ selection }) {
      if (!selection) return;
      const [x0, x1] = selection.map(xBrush.invert);
      x.domain([x0, x1]);
      mainG.select(".x-axis").call(xAxis);
      series.forEach(s => {
        lines[s.key].attr("d", lineGen(s.key, x));
      });
      checks.brushSync = true;
    }

    function zoomed(event) {
      const t = event.transform;
      const zx = t.rescaleX(xBrush);
      x.domain(zx.domain());
      mainG.select(".x-axis").call(xAxis.scale(zx));
      series.forEach(s => {
        lines[s.key].attr("d", lineGen(s.key, zx));
      });
      const newBrushRange = x.domain().map(xBrush);
      brushG.select(".x-brush").call(brush.move, newBrushRange);
      checks.zoomSync = true;
    }

    const legend = svg
      .append("g")
      .attr("class", "legend")
      .attr("transform", `translate(${width - margin.right + 10},${margin.top})`);
    series.forEach((s, i) => {
      const g = legend
        .append("g")
        .attr("transform", `translate(0,${i * 18})`)
        .style("cursor", "pointer")
        .on("click", () => {
          visible[s.key] = !visible[s.key];
          const active = visible[s.key];
          lines[s.key]
            .transition()
            .duration(300)
            .style("opacity", active ? 1 : 0)
            .style("stroke-width", active ? 1.5 : 0);
          brushLines[s.key]
            .transition()
            .duration(300)
            .style("opacity", active ? 1 : 0)
            .style("stroke-width", active ? 1 : 0);
          g.select("rect")
            .transition()
            .duration(300)
            .style("opacity", active ? 1 : 0.25);
          checks.legendToggle = true;
        });
      g.append("rect").attr("width", 12).attr("height", 12).attr("fill", color(s.key));
      g.append("text").attr("x", 16).attr("y", 10).text(s.name);
    });

    const bisectDate = d3.bisector(d => d.date).left;
    const overlay = mainG
      .append("rect")
      .attr("fill", "none")
      .attr("pointer-events", "all")
      .attr("width", width - margin.left - margin.right)
      .attr("height", innerHeight);

    const focusLine = mainG
      .append("line")
      .attr("stroke", "#555")
      .attr("stroke-dasharray", "4 2")
      .style("opacity", 0);

    overlay
      .on("mousemove", event => {
        const [mx] = d3.pointer(event);
        const x0 = x.invert(mx);
        const i = bisectDate(filtered, x0, 1);
        const d0 = filtered[i - 1];
        const d1 = filtered[i];
        const d = !d0 ? d1 : !d1 ? d0 : x0 - d0.date > d1.date - x0 ? d1 : d0;
        if (!d) return;
        const cx = x(d.date) + margin.left;
        focusLine
          .attr("x1", x(d.date))
          .attr("x2", x(d.date))
          .attr("y1", 0)
          .attr("y2", innerHeight)
          .style("opacity", 1);
        const linesText = [
          `T: ${d.temperature.toFixed(1)}`,
          `H: ${d.humidity.toFixed(1)}`,
          `W: ${d.wind.toFixed(1)}`,
        ].join(" | ");
        tooltipEl.style.display = "block";
        tooltipEl.style.left = cx + "px";
        tooltipEl.style.top = margin.top + 10 + "px";
        tooltipEl.textContent =
          d.date.toISOString().slice(0, 10) + " – " + linesText;
        checks.tooltip = true;
      })
      .on("mouseleave", () => {
        focusLine.style("opacity", 0);
        tooltipEl.style.display = "none";
      });

    const failures = Object.entries(checks)
      .filter(([, v]) => !v)
      .map(([k]) => k);
    if (failures.length === 0) {
      appendStatus(qid + ": PASS");
      summary[qid] = "PASS";
    } else {
      appendStatus(qid + ": FAIL – " + failures.join(", "));
      summary[qid] = "FAIL";
    }
    setSummaryAndMaybeRenderBox();
  } catch (err) {
    console.error(qid + " error:", err);
    appendStatus(qid + ": FAIL – " + err.message);
    summary[qid] = "FAIL";
    setSummaryAndMaybeRenderBox();
  }
}

async function initQ2() {
  const qid = "Q2";
  appendStatus(qid + ": loading JSON…");
  const checks = {
    jsonLoaded: false,
    simulation: false,
    dragging: false,
    hover: false,
    clickFix: false,
    colored: false,
  };
  try {
    const raw = await d3.json("data/network.json");
    let nodes = raw.nodes || raw.Nodes || raw.vertices || [];
    let links = raw.links || raw.Links || raw.edges || [];
    console.log("Q2 raw counts:", { nodes: nodes.length, links: links.length });
    checks.jsonLoaded = nodes.length > 0 && links.length >= 0;

    const idField =
      nodes[0] &&
      (nodes[0].id ? "id" : nodes[0].name ? "name" : Object.keys(nodes[0])[0]);
    const sourceField =
      links[0] &&
      (links[0].source ? "source" : links[0].from ? "from" : Object.keys(links[0])[0]);
    const targetField =
      links[0] &&
      (links[0].target ? "target" : links[0].to ? "to" : Object.keys(links[0])[1]);

    nodes = nodes.map((d, i) => ({ ...d, id: d[idField] ?? i }));
    links = links.map(l => ({
      ...l,
      source: typeof l[sourceField] === "object" ? l[sourceField].id : l[sourceField],
      target: typeof l[targetField] === "object" ? l[targetField].id : l[targetField],
    }));

    console.log("Q2 normalized example node/link:", nodes[0], links[0]);

    const svg = d3.select("#q2-svg");
    svg.selectAll("*").remove();
    const width = +svg.attr("width");
    const height = +svg.attr("height");

    const g = svg.append("g");

    const zoom = d3
      .zoom()
      .scaleExtent([0.2, 4])
      .on("zoom", event => {
        g.attr("transform", event.transform);
      });
    svg.call(zoom);

    const color = d3.scaleOrdinal(d3.schemeCategory10);

    const link = g
      .append("g")
      .attr("stroke", "#999")
      .attr("stroke-opacity", 0.6)
      .selectAll("line")
      .data(links)
      .join("line")
      .attr("stroke-width", d => Math.sqrt(d.value || 1));

    const node = g
      .append("g")
      .attr("stroke", "#fff")
      .attr("stroke-width", 1)
      .selectAll("circle")
      .data(nodes)
      .join("circle")
      .attr("r", 5)
      .attr("fill", d => {
        const c = color(d.group || 0);
        if (!checks.colored && d.group !== undefined) checks.colored = true;
        return c;
      })
      .call(
        d3
          .drag()
          .on("start", dragstarted)
          .on("drag", dragged)
          .on("end", dragended)
      )
      .on("mouseover", mouseover)
      .on("mouseout", mouseout)
      .on("click", nodeClicked);

    const label = g
      .append("g")
      .attr("font-size", 10)
      .attr("pointer-events", "none")
      .selectAll("text")
      .data(nodes)
      .join("text")
      .text(d => d.id);

    const simulation = d3
      .forceSimulation(nodes)
      .force("link", d3.forceLink(links).id(d => d.id).distance(60).strength(1))
      .force("charge", d3.forceManyBody().strength(-120))
      .force("center", d3.forceCenter(width / 2, height / 2));

    simulation.on("tick", () => {
      link
        .attr("x1", d => d.source.x)
        .attr("y1", d => d.source.y)
        .attr("x2", d => d.target.x)
        .attr("y2", d => d.target.y);
      node.attr("cx", d => d.x).attr("cy", d => d.y);
      label.attr("x", d => d.x + 6).attr("y", d => d.y + 3);
    });

    setTimeout(() => {
      simulation.alphaTarget(0).stop();
      checks.simulation = true;
    }, 3000);

    const adjacency = {};
    links.forEach(l => {
      const s = l.source.id ?? l.source;
      const t = l.target.id ?? l.target;
      adjacency[s] = adjacency[s] || new Set();
      adjacency[t] = adjacency[t] || new Set();
      adjacency[s].add(t);
      adjacency[t].add(s);
    });

    function isNeighbor(a, b) {
      if (a.id === b.id) return true;
      return adjacency[a.id] && adjacency[a.id].has(b.id);
    }

    function mouseover(event, d) {
      node.style("opacity", o => (isNeighbor(d, o) ? 1 : 0.1));
      link
        .style("opacity", o =>
          o.source.id === d.id || o.target.id === d.id ? 1 : 0.05
        )
        .attr("stroke-width", o =>
          o.source.id === d.id || o.target.id === d.id ? 2 : 1
        );
      checks.hover = true;
    }

    function mouseout() {
      node.style("opacity", 1);
      link.style("opacity", 0.6).attr("stroke-width", 1);
    }

    function dragstarted(event, d) {
      if (!event.active) simulation.alphaTarget(0.3).restart();
      d.fx = d.x;
      d.fy = d.y;
    }

    function dragged(event, d) {
      d.fx = event.x;
      d.fy = event.y;
      checks.dragging = true;
    }

    function dragended(event, d) {
      if (!event.active) simulation.alphaTarget(0);
    }

    function nodeClicked(event, d) {
      const fixed = d.fx != null || d.fy != null;
      if (fixed) {
        d.fx = null;
        d.fy = null;
      } else {
        d.fx = d.x;
        d.fy = d.y;
      }
      d3.select(this)
        .attr("stroke-width", fixed ? 1 : 3)
        .attr("stroke", fixed ? "#fff" : "#000");
      checks.clickFix = true;
    }

    const failures = Object.entries(checks)
      .filter(([, v]) => !v)
      .map(([k]) => k);
    if (failures.length === 0) {
      appendStatus(qid + ": PASS");
      summary[qid] = "PASS";
    } else {
      appendStatus(qid + ": FAIL – " + failures.join(", "));
      summary[qid] = "FAIL";
    }
    setSummaryAndMaybeRenderBox();
  } catch (err) {
    console.error(qid + " error:", err);
    appendStatus(qid + ": FAIL – " + err.message);
    summary[qid] = "FAIL";
    setSummaryAndMaybeRenderBox();
  }
}

async function initQ3() {
  const qid = "Q3";
  appendStatus(qid + ": loading JSON…");
  const checks = {
    jsonLoaded: false,
    rendered: false,
    clickZoom: false,
    search: false,
    breadcrumbs: false,
  };
  try {
    const raw = await d3.json("data/software.json");
    checks.jsonLoaded = !!raw;
    const root = d3.hierarchy(raw).sum(d => d.loc || d.size || 1);
    console.log("Q3 hierarchy sum:", root.value);
    const maxDepth = d3.max(root.descendants(), d => d.depth);
    const useSunburst = maxDepth <= 4;
    console.log("Q3 using:", useSunburst ? "sunburst" : "treemap");

    const svg = d3.select("#q3-svg");
    svg.selectAll("*").remove();
    const width = +svg.attr("width");
    const height = +svg.attr("height");
    const radius = Math.min(width, height) / 2 - 20;
    const g = svg.append("g").attr("transform", `translate(${width / 2},${height / 2})`);

    const color = d3.scaleOrdinal(d3.schemeCategory10);
    const breadcrumbsEl = document.getElementById("q3-breadcrumbs");

    let currentNode = root;

    if (useSunburst) {
      const partition = d3.partition().size([2 * Math.PI, radius]);
      partition(root);

      const arc = d3
        .arc()
        .startAngle(d => d.x0)
        .endAngle(d => d.x1)
        .innerRadius(d => d.y0)
        .outerRadius(d => d.y1);

      const nodes = g
        .selectAll("path")
        .data(root.descendants().filter(d => d.depth))
        .join("path")
        .attr("fill", d =>
          color(d.ancestors().map(a => a.data.name).reverse().join("/"))
        )
        .attr("d", arc)
        .on("click", (event, d) => {
          focusOn(d);
          checks.clickZoom = true;
        })
        .on("mousemove", (event, d) => {
          const path = d.ancestors().reverse().map(x => x.data.name).join("/");
          tooltipEl.style.display = "block";
          tooltipEl.style.left = event.pageX + "px";
          tooltipEl.style.top = event.pageY + "px";
          tooltipEl.textContent = path + " – LOC: " + (d.value ?? 0);
        })
        .on("mouseleave", () => {
          tooltipEl.style.display = "none";
        });

      function focusOn(d) {
        currentNode = d;
        const xDomain = [d.x0, d.x1];
        const yDomain = [d.y0, radius];
        const xd = d3.scaleLinear().domain(xDomain).range([0, 2 * Math.PI]);
        const yd = d3.scaleLinear().domain(yDomain).range([0, radius]);

        nodes
          .transition()
          .duration(750)
          .attrTween("d", node => {
            const i = d3.interpolate(
              { x0: node.x0, x1: node.x1, y0: node.y0, y1: node.y1 },
              {
                x0: Math.max(0, Math.min(1, (node.x0 - d.x0) / (d.x1 - d.x0))) *
                  2 *
                  Math.PI,
                x1: Math.max(0, Math.min(1, (node.x1 - d.x0) / (d.x1 - d.x0))) *
                  2 *
                  Math.PI,
                y0: Math.max(0, node.y0 - d.y0),
                y1: Math.max(0, node.y1 - d.y0),
              }
            );
            return t => {
              const b = i(t);
              return d3
                .arc()
                .startAngle(b.x0)
                .endAngle(b.x1)
                .innerRadius(b.y0)
                .outerRadius(b.y1)();
            };
          });
        updateBreadcrumbs(d);
      }

      focusOn(root);
    } else {
      const treemap = d3.treemap().size([width, height]).padding(1);
      treemap(root);

      const nodes = svg
        .selectAll("g.node")
        .data(root.descendants())
        .join("g")
        .attr("class", "node")
        .attr("transform", d => `translate(${d.x0},${d.y0})`)
        .on("click", (event, d) => {
          currentNode = d;
          updateBreadcrumbs(d);
          checks.clickZoom = true;
        })
        .on("mousemove", (event, d) => {
          const path = d.ancestors().reverse().map(x => x.data.name).join("/");
          tooltipEl.style.display = "block";
          tooltipEl.style.left = event.pageX + "px";
          tooltipEl.style.top = event.pageY + "px";
          tooltipEl.textContent = path + " – LOC: " + (d.value ?? 0);
        })
        .on("mouseleave", () => {
          tooltipEl.style.display = "none";
        });

      nodes
        .append("rect")
        .attr("fill", d => color(d.height))
        .attr("width", d => Math.max(0, d.x1 - d.x0))
        .attr("height", d => Math.max(0, d.y1 - d.y0));

      nodes
        .append("text")
        .attr("dx", 3)
        .attr("dy", 10)
        .text(d => d.data.name)
        .attr("font-size", "9px")
        .attr("pointer-events", "none");

      updateBreadcrumbs(root);
    }

    checks.rendered = true;

    function updateBreadcrumbs(node) {
      const path = node.ancestors().reverse();
      breadcrumbsEl.innerHTML = "";
      path.forEach(d => {
        const span = document.createElement("span");
        span.textContent = d.data.name || "(root)";
        span.onclick = () => {
          currentNode = d;
          updateBreadcrumbs(d);
        };
        breadcrumbsEl.appendChild(span);
      });
      checks.breadcrumbs = true;
    }

    const searchInput = document.getElementById("q3-search");
    const searchInfo = document.getElementById("q3-search-info");
    searchInput.addEventListener("keydown", e => {
      if (e.key !== "Enter") return;
      const term = searchInput.value.trim().toLowerCase();
      if (!term) return;
      const matches = root
        .descendants()
        .filter(d => (d.data.name || "").toLowerCase().includes(term));
      if (!matches.length) {
        searchInfo.textContent = "No matches";
        return;
      }
      searchInfo.textContent = `${matches.length} match(es)`;
      const first = matches[0];
      checks.search = true;

      const pathSet = new Set(first.ancestors());

      d3.selectAll("#q3-svg path, #q3-svg rect")
        .style("stroke", null)
        .style("stroke-width", null)
        .style("opacity", 0.3);

      d3.selectAll("#q3-svg path, #q3-svg rect")
        .filter(function (d) {
          return pathSet.has(d);
        })
        .style("opacity", 1)
        .style("stroke", "#ff9800")
        .style("stroke-width", 2);

      updateBreadcrumbs(first);
    });

    const failures = Object.entries(checks)
      .filter(([, v]) => !v)
      .map(([k]) => k);
    if (failures.length === 0) {
      appendStatus(qid + ": PASS");
      summary[qid] = "PASS";
    } else {
      appendStatus(qid + ": FAIL – " + failures.join(", "));
      summary[qid] = "FAIL";
    }
    setSummaryAndMaybeRenderBox();
  } catch (err) {
    console.error(qid + " error:", err);
    appendStatus(qid + ": FAIL – " + err.message);
    summary[qid] = "FAIL";
    setSummaryAndMaybeRenderBox();
  }
}

function generateData() {
  return Array.from({ length: 10 }, () => ({
    id: crypto.randomUUID(),
    value: Math.random() * 100,
  }));
}

async function initQ4() {
  const qid = "Q4";
  appendStatus(qid + ": initializing…");
  const checks = {
    ticking: false,
    enterUpdateExit: false,
    sorted: false,
    scrolling: false,
    pauseResume: false,
    threshold: false,
  };
  try {
    const barSvg = d3.select("#q4-bars-svg");
    const lineSvg = d3.select("#q4-line-svg");
    barSvg.selectAll("*").remove();
    lineSvg.selectAll("*").remove();

    const barW = +barSvg.attr("width");
    const barH = +barSvg.attr("height");
    const lineW = +lineSvg.attr("width");
    const lineH = +lineSvg.attr("height");
    const margin = { top: 10, right: 20, bottom: 24, left: 40 };
    const innerBarH = barH - margin.top - margin.bottom;
    const innerBarW = barW - margin.left - margin.right;
    const innerLineH = lineH - margin.top - margin.bottom;
    const innerLineW = lineW - margin.left - margin.right;

    const barG = barSvg
      .append("g")
      .attr("transform", `translate(${margin.left},${margin.top})`);
    const lineG = lineSvg
      .append("g")
      .attr("transform", `translate(${margin.left},${margin.top})`);

    const xBar = d3.scaleBand().padding(0.1).range([0, innerBarW]);
    const yBar = d3.scaleLinear().domain([0, 100]).range([innerBarH, 0]);
    const xLine = d3.scaleLinear().domain([0, 50]).range([0, innerLineW]);
    const yLine = d3.scaleLinear().domain([0, 100]).range([innerLineH, 0]);

    barG
      .append("g")
      .attr("class", "x-axis")
      .attr("transform", `translate(0,${innerBarH})`);
    barG.append("g").attr("class", "y-axis").call(d3.axisLeft(yBar));

    lineG
      .append("g")
      .attr("class", "x-axis-line")
      .attr("transform", `translate(0,${innerLineH})`)
      .call(d3.axisBottom(xLine).ticks(5));
    lineG.append("g").attr("class", "y-axis-line").call(d3.axisLeft(yLine));

    const clipId = "q4-line-clip";
    lineSvg
      .append("defs")
      .append("clipPath")
      .attr("id", clipId)
      .append("rect")
      .attr("width", innerLineW)
      .attr("height", innerLineH);

    const linePathG = lineG.append("g").attr("clip-path", `url(#${clipId})`);

    const lineGen = d3
      .line()
      .x((d, i) => xLine(i))
      .y(d => yLine(d));

    let history = [];
    let currentData = generateData();
    let running = true;

    const toggleBtn = document.getElementById("q4-toggle");
    const thresholdInput = document.getElementById("q4-threshold");
    const thresholdValue = document.getElementById("q4-threshold-value");
    const statusText = document.getElementById("q4-status-text");
    const meanText = document.getElementById("q4-mean");

    function updateBars(data) {
      data.sort((a, b) => d3.descending(a.value, b.value));
      xBar.domain(data.map((d, i) => i));

      const bars = barG.selectAll("rect.bar").data(data, d => d.id);

      const threshold = +thresholdInput.value;

      const barsEnter = bars
        .enter()
        .append("rect")
        .attr("class", "bar")
        .attr("x", innerBarW)
        .attr("width", xBar.bandwidth())
        .attr("y", innerBarH)
        .attr("height", 0)
        .attr("fill", d => (d.value >= threshold ? "red" : "#90caf9"));

      barsEnter
        .merge(bars)
        .transition()
        .duration(600)
        .attr("x", (d, i) => xBar(i))
        .attr("y", d => yBar(d.value))
        .attr("height", d => innerBarH - yBar(d.value))
        .attr("width", xBar.bandwidth())
        .attr("fill", d => (d.value >= threshold ? "red" : "#90caf9"));

      bars
        .exit()
        .transition()
        .duration(400)
        .attr("y", innerBarH)
        .attr("height", 0)
        .style("opacity", 0)
        .remove();

      barG.select(".x-axis").transition().call(d3.axisBottom(xBar).tickFormat(""));

      checks.enterUpdateExit = true;
      checks.sorted = true;
      checks.threshold = true;
    }

    function updateLine(mean) {
      if (!Number.isFinite(mean)) return;
      history.push(mean);
      const maxPoints = 50;
      if (history.length > maxPoints) {
        history = history.slice(history.length - maxPoints);
      }
      const data = history.slice();
      xLine.domain([0, maxPoints - 1]);
      yLine.domain([0, 100]);

      const lineSel = linePathG.selectAll("path").data([data]);
      lineSel
        .enter()
        .append("path")
        .attr("fill", "none")
        .attr("stroke", "#ff6f00")
        .attr("stroke-width", 1.5)
        .merge(lineSel)
        .transition()
        .duration(600)
        .attr("d", lineGen);

      lineSel.exit().remove();
      checks.scrolling = true;
    }

    function tick() {
      if (!running) return;
      checks.ticking = true;
      currentData = generateData();
      const mean = d3.mean(currentData, d => d.value) ?? 0;
      meanText.textContent = mean.toFixed(1);
      updateBars(currentData);
      updateLine(mean);
    }

    toggleBtn.addEventListener("click", () => {
      running = !running;
      toggleBtn.textContent = running ? "Pause" : "Resume";
      statusText.textContent = running ? "Running" : "Paused";
      checks.pauseResume = true;
    });

    thresholdInput.addEventListener("input", () => {
      thresholdValue.textContent = thresholdInput.value;
      updateBars(currentData);
    });

    tick();
    const interval = setInterval(() => {
      if (!document.body.contains(barSvg.node())) {
        clearInterval(interval);
        return;
      }
      tick();
    }, 2000);

    setTimeout(() => {
      const failures = Object.entries(checks)
        .filter(([, v]) => !v)
        .map(([k]) => k);
      if (failures.length === 0) {
        appendStatus(qid + ": PASS");
        summary[qid] = "PASS";
      } else {
        appendStatus(qid + ": FAIL – " + failures.join(", "));
        summary[qid] = "FAIL";
      }
      setSummaryAndMaybeRenderBox();
    }, 6500);
  } catch (err) {
    console.error(qid + " error:", err);
    appendStatus(qid + ": FAIL – " + err.message);
    summary[qid] = "FAIL";
    setSummaryAndMaybeRenderBox();
  }
}

(async function main() {
  appendStatus("Initializing visualizations…");
  await initQ1();
  await initQ2();
  await initQ3();
  await initQ4();
})();
import * as d3 from "https://cdn.jsdelivr.net/npm/d3@7/dist/d3.min.js";

function appendStatus(msg) {
  console.log(msg);
  statusEl.textContent += "\\n" + msg;
}



async function initQ1() {
  const checks = {
    csvLoaded: false,
    threeLines: false,
    brushSync: false,
    zoomSync: false,
    legendToggle: false,
    tooltip: false,
  };
  try {
    const parseDate = d3.timeParse("%Y-%m-%d");
    const data = await d3.csv("data/weather.csv", d => {
      const row = {
        date: parseDate(d.date || d.Date || d.time || d.timestamp),
        temperature: +d.temperature || +d.temp,
        humidity: +d.humidity || +d.hum,
        wind: +d.wind || +d.windSpeed || +d.wind_speed
      };
      if (!checks.csvLoaded) {
        console.log("Q1 parsed row example:", row, d);
        checks.csvLoaded = true;
      }
      return row;
    });
    const filtered = data.filter(d => d.date && !Number.isNaN(d.temperature) && !Number.isNaN(d.humidity) && !Number.isNaN(d.wind));

    const svg = d3.select("#q1-svg");
    svg.selectAll("*").remove();
    const width = +svg.attr("width");
    const height = +svg.attr("height");
    const margin = { top: 20, right: 80, bottom: 110, left: 50 };
    const marginBrush = { top: height - 90, right: 80, bottom: 20, left: 50 };
    const innerHeight = height - margin.top - margin.bottom;
    const brushHeight = height - marginBrush.top - marginBrush.bottom;

    const x = d3.scaleTime().range([0, width - margin.left - margin.right]);
    const xBrush = d3.scaleTime().range([0, width - margin.left - margin.right]);
    const y = d3.scaleLinear().range([innerHeight, 0]);
    const color = d3.scaleOrdinal(d3.schemeCategory10).domain(["temperature", "humidity", "wind"]);

    const series = [
      { key: "temperature", name: "Temperature" },
      { key: "humidity", name: "Humidity" },
      { key: "wind", name: "Wind" },
    ];
    const visible = { temperature: true, humidity: true, wind: true };

    x.domain(d3.extent(filtered, d => d.date));
    xBrush.domain(x.domain());

    const yExtent = [
      d3.min(series, s => d3.min(filtered, d => d[s.key])),
      d3.max(series, s => d3.max(filtered, d => d[s.key])),
    ];
    y.domain(yExtent).nice();

    const mainG = svg.append("g").attr("transform", `translate(${margin.left},${margin.top})`);
    const brushG = svg.append("g").attr("transform", `translate(${marginBrush.left},${marginBrush.top})`);

    const xAxis = d3.axisBottom(x);
    const yAxis = d3.axisLeft(y);
    const xAxisBrush = d3.axisBottom(xBrush);

    mainG.append("g")
      .attr("class", "x-axis")
      .attr("transform", `translate(0,${innerHeight})`)
      .call(xAxis);
    mainG.append("g")
      .attr("class", "y-axis")
      .call(yAxis);

    mainG.append("g")
      .attr("class", "grid")
      .call(d3.axisLeft(y).tickSize(- (width - margin.left - margin.right)).tickFormat(""));

    brushG.append("g")
      .attr("class", "x-axis-brush")
      .attr("transform", `translate(0,${brushHeight})`)
      .call(xAxisBrush);

    const lineGen = (key, scaleX) => d3.line()
      .x(d => scaleX(d.date))
      .y(d => y(d[key]));

    const linesG = mainG.append("g").attr("class", "lines");
    const lines = {};
    series.forEach(s => {
      lines[s.key] = linesG.append("path")
        .datum(filtered)
        .attr("fill", "none")
        .attr("stroke", color(s.key))
        .attr("stroke-width", 1.5)
        .attr("class", `line-${s.key}`)
        .attr("d", lineGen(s.key, x));
    });

    checks.threeLines = Object.keys(lines).length === 3;

    const brushLinesG = brushG.append("g").attr("class", "brush-lines");
    const brushLines = {};
    series.forEach(s => {
      brushLines[s.key] = brushLinesG.append("path")
        .datum(filtered)
        .attr("fill", "none")
        .attr("stroke", color(s.key))
        .attr("stroke-width", 1)
        .attr("d", lineGen(s.key, xBrush));
    });

    const brush = d3.brushX()
      .extent([[0, 0], [width - margin.left - margin.right, brushHeight]])
      .on("brush end", brushed);

    const defaultSelection = [xBrush.domain()[0], xBrush.domain()[1]];
    const brushSelection = d3.brushSelection(brushG.node());
    brushG.append("g")
      .attr("class", "x-brush")
      .call(brush)
      .call(g => g.call(brush.move, defaultSelection.map(xBrush)));

    const zoom = d3.zoom()
      .scaleExtent([1, 20])
      .translateExtent([[0, 0], [width - margin.left - margin.right, innerHeight]])
      .extent([[0, 0], [width - margin.left - margin.right, innerHeight]])
      .on("zoom", zoomed);

    svg.call(zoom).on("dblclick.zoom", null);

    function brushed({ selection }) {
      if (!selection) return;
      const [x0, x1] = selection.map(xBrush.invert);
      x.domain([x0, x1]);
      mainG.select(".x-axis").call(xAxis);
      series.forEach(s => {
        lines[s.key].attr("d", lineGen(s.key, x));
      });
      checks.brushSync = true;
    }

    function zoomed(event) {
      const t = event.transform;
      const zx = t.rescaleX(xBrush);
      x.domain(zx.domain());
      mainG.select(".x-axis").call(xAxis.scale(zx));
      series.forEach(s => {
        lines[s.key].attr("d", lineGen(s.key, zx));
      });
      const newBrushRange = x.domain().map(xBrush);
      brushG.select(".x-brush").call(brush.move, newBrushRange);
      checks.zoomSync = true;
    }

    const legend = svg.append("g")
      .attr("class", "legend")
      .attr("transform", `translate(${width - margin.right + 10},${margin.top})`);
    series.forEach((s, i) => {
      const g = legend.append("g")
        .attr("transform", `translate(0,${i * 18})`)
        .style("cursor", "pointer")
        .on("click", () => {
          visible[s.key] = !visible[s.key];
          const active = visible[s.key];
          lines[s.key]
            .transition().duration(300)
            .style("opacity", active ? 1 : 0)
            .style("stroke-width", active ? 1.5 : 0);
          brushLines[s.key]
            .transition().duration(300)
            .style("opacity", active ? 1 : 0)
            .style("stroke-width", active ? 1 : 0);
          g.select("rect")
            .transition().duration(300)
            .style("opacity", active ? 1 : 0.25);
          checks.legendToggle = true;
        });
      g.append("rect")
        .attr("width", 12)
        .attr("height", 12)
        .attr("fill", color(s.key));
      g.append("text")
        .attr("x", 16)
        .attr("y", 10)
        .text(s.name);
    });

    const bisectDate = d3.bisector(d => d.date).left;
    const overlay = mainG.append("rect")
      .attr("fill", "none")
      .attr("pointer-events", "all")
      .attr("width", width - margin.left - margin.right)
      .attr("height", innerHeight);

    const focusLine = mainG.append("line")
      .attr("stroke", "#555")
      .attr("stroke-dasharray", "4 2")
      .style("opacity", 0);

    overlay
      .on("mousemove", (event) => {
        const [mx] = d3.pointer(event);
        const x0 = x.invert(mx);
        const i = bisectDate(filtered, x0, 1);
        const d0 = filtered[i - 1];
        const d1 = filtered[i];
        const d = !d0 ? d1 : !d1 ? d0 : (x0 - d0.date > d1.date - x0 ? d1 : d0);
        if (!d) return;
        const cx = x(d.date) + margin.left;
        focusLine
          .attr("x1", x(d.date))
          .attr("x2", x(d.date))
          .attr("y1", 0)
          .attr("y2", innerHeight)
          .style("opacity", 1);
        const linesText = [
          `T: ${d.temperature.toFixed(1)}`,
          `H: ${d.humidity.toFixed(1)}`,
          `W: ${d.wind.toFixed(1)}`
        ].join(" | ");
        tooltipEl.style.display = "block";
        tooltipEl.style.left = cx + "px";
        tooltipEl.style.top = (margin.top + 10) + "px";
        tooltipEl.textContent = d.date.toISOString().slice(0, 10) + " – " + linesText;
        checks.tooltip = true;
      })
      .on("mouseleave", () => {
        focusLine.style("opacity", 0);
        tooltipEl.style.display = "none";
      });

    const failures = Object.entries(checks).filter(([, v]) => !v).map(([k]) => k);
    if (failures.length === 0) {
      appendStatus(qid + ": PASS");
      summary[qid] = "PASS";
    } else {
      appendStatus(qid + ": FAIL – " + failures.join(", "));
      summary[qid] = "FAIL";
    }
    setSummaryAndMaybeRenderBox();
  } catch (err) {
    console.error(qid + " error:", err);
    appendStatus(qid + ": FAIL – " + err.message);
    summary[qid] = "FAIL";
    setSummaryAndMaybeRenderBox();
  }
}

async function initQ2() {
  const qid = "Q2";
  appendStatus(qid + ": loading JSON…");
  const checks = {
    jsonLoaded: false,
    simulation: false,
    dragging: false,
    hover: false,
    clickFix: false,
    colored: false,
  };
  try {
    const raw = await d3.json("data/network.json");
    let nodes = raw.nodes || raw.Nodes || raw.vertices || [];
    let links = raw.links || raw.Links || raw.edges || [];
    console.log("Q2 raw counts:", { nodes: nodes.length, links: links.length });
    checks.jsonLoaded = nodes.length > 0 && links.length >= 0;

    const idField = nodes[0] && (nodes[0].id ? "id" : nodes[0].name ? "name" : Object.keys(nodes[0])[0]);
    const sourceField = links[0] && (links[0].source ? "source" : links[0].from ? "from" : Object.keys(links[0])[0]);
    const targetField = links[0] && (links[0].target ? "target" : links[0].to ? "to" : Object.keys(links[0])[1]);

    nodes = nodes.map((d, i) => ({ ...d, id: d[idField] ?? i }));
    links = links.map(l => ({
      ...l,
      source: typeof l[sourceField] === "object" ? l[sourceField].id : l[sourceField],
      target: typeof l[targetField] === "object" ? l[targetField].id : l[targetField],
    }));

    console.log("Q2 normalized example node/link:", nodes[0], links[0]);

    const svg = d3.select("#q2-svg");
    svg.selectAll("*").remove();
    const width = +svg.attr("width");
    const height = +svg.attr("height");

    const g = svg.append("g");

    const zoom = d3.zoom()
      .scaleExtent([0.2, 4])
      .on("zoom", (event) => {
        g.attr("transform", event.transform);
      });
    svg.call(zoom);

    const color = d3.scaleOrdinal(d3.schemeCategory10);

    const link = g.append("g")
      .attr("stroke", "#999")
      .attr("stroke-opacity", 0.6)
      .selectAll("line")
      .data(links)
      .join("line")
      .attr("stroke-width", d => Math.sqrt(d.value || 1));

    const node = g.append("g")
      .attr("stroke", "#fff")
      .attr("stroke-width", 1.0)
      .selectAll("circle")
      .data(nodes)
      .join("circle")
      .attr("r", 5)
      .attr("fill", d => {
        const c = color(d.group || 0);
        if (!checks.colored && d.group !== undefined) checks.colored = true;
        return c;
      })
      .call(d3.drag()
        .on("start", dragstarted)
        .on("drag", dragged)
        .on("end", dragended))
      .on("mouseover", mouseover)
      .on("mouseout", mouseout)
      .on("click", nodeClicked);

    const label = g.append("g")
      .attr("font-size", 10)
      .attr("pointer-events", "none")
      .selectAll("text")
      .data(nodes)
      .join("text")
      .text(d => d.id);

    const simulation = d3.forceSimulation(nodes)
      .force("link", d3.forceLink(links).id(d => d.id).distance(60).strength(1))
      .force("charge", d3.forceManyBody().strength(-120))
      .force("center", d3.forceCenter(width / 2, height / 2));

    simulation.on("tick", () => {
      link
        .attr("x1", d => d.source.x)
        .attr("y1", d => d.source.y)
        .attr("x2", d => d.target.x)
        .attr("y2", d => d.target.y);
      node
        .attr("cx", d => d.x)
        .attr("cy", d => d.y);
      label
        .attr("x", d => d.x + 6)
        .attr("y", d => d.y + 3);
    });

    setTimeout(() => {
      simulation.alphaTarget(0).stop();
      checks.simulation = true;
    }, 3000);

    const adjacency = {};
    links.forEach(l => {
      const s = l.source.id ?? l.source;
      const t = l.target.id ?? l.target;
      adjacency[s] = adjacency[s] || new Set();
      adjacency[t] = adjacency[t] || new Set();
      adjacency[s].add(t);
      adjacency[t].add(s);
    });

    function isNeighbor(a, b) {
      if (a.id === b.id) return true;
      return adjacency[a.id] && adjacency[a.id].has(b.id);
    }

    function mouseover(event, d) {
      node.style("opacity", o => isNeighbor(d, o) ? 1 : 0.1);
      link.style("opacity", o => (o.source.id === d.id || o.target.id === d.id) ? 1 : 0.05)
        .attr("stroke-width", o => (o.source.id === d.id || o.target.id === d.id) ? 2 : 1);
      checks.hover = true;
    }

    function mouseout() {
      node.style("opacity", 1);
      link.style("opacity", 0.6).attr("stroke-width", 1);
    }

    function dragstarted(event, d) {
      if (!event.active) simulation.alphaTarget(0.3).restart();
      d.fx = d.x;
      d.fy = d.y;
    }

    function dragged(event, d) {
      d.fx = event.x;
      d.fy = event.y;
      checks.dragging = true;
    }

    function dragended(event, d) {
      if (!event.active) simulation.alphaTarget(0);
    }

    function nodeClicked(event, d) {
      const fixed = d.fx != null || d.fy != null;
      if (fixed) {
        d.fx = null;
        d.fy = null;
      } else {
        d.fx = d.x;
        d.fy = d.y;
      }
      d3.select(this)
        .attr("stroke-width", fixed ? 1.0 : 3.0)
        .attr("stroke", fixed ? "#fff" : "#000");
      checks.clickFix = true;
    }

    const failures = Object.entries(checks).filter(([, v]) => !v).map(([k]) => k);
    if (failures.length === 0) {
      appendStatus(qid + ": PASS");
      summary[qid] = "PASS";
    } else {
      appendStatus(qid + ": FAIL – " + failures.join(", "));
      summary[qid] = "FAIL";
    }
    setSummaryAndMaybeRenderBox();
  } catch (err) {
    console.error(qid + " error:", err);
    appendStatus(qid + ": FAIL – " + err.message);
    summary[qid] = "FAIL";
    setSummaryAndMaybeRenderBox();
  }
}

async function initQ3() {
  const qid = "Q3";
  appendStatus(qid + ": loading JSON…");
  const checks = {
    jsonLoaded: false,
    rendered: false,
    clickZoom: false,
    search: false,
    breadcrumbs: false,
  };
  try {
    const raw = await d3.json("data/software.json");
    checks.jsonLoaded = !!raw;
    const root = d3.hierarchy(raw).sum(d => d.loc || d.size || 1);
    console.log("Q3 hierarchy sum:", root.value);
    const maxDepth = d3.max(root.descendants(), d => d.depth);
    const useSunburst = maxDepth <= 4;
    console.log("Q3 using:", useSunburst ? "sunburst" : "treemap");

    const svg = d3.select("#q3-svg");
    svg.selectAll("*").remove();
    const width = +svg.attr("width");
    const height = +svg.attr("height");
    const radius = Math.min(width, height) / 2 - 20;
    const g = svg.append("g").attr("transform", `translate(${width / 2},${height / 2})`);

    const color = d3.scaleOrdinal(d3.schemeCategory10);

    const breadcrumbsEl = document.getElementById("q3-breadcrumbs");

    let currentNode = root;

    if (useSunburst) {
      const partition = d3.partition()
        .size([2 * Math.PI, radius]);
      partition(root);

      const arc = d3.arc()
        .startAngle(d => d.x0)
        .endAngle(d => d.x1)
        .innerRadius(d => d.y0)
        .outerRadius(d => d.y1);

      const nodes = g.selectAll("path")
        .data(root.descendants().filter(d => d.depth))
        .join("path")
        .attr("fill", d => color(d.ancestors().map(d => d.data.name).reverse().join("/")))
        .attr("d", arc)
        .on("click", (event, d) => {
          focusOn(d);
          checks.clickZoom = true;
        })
        .on("mousemove", (event, d) => {
          const path = d.ancestors().reverse().map(x => x.data.name).join("/");
          tooltipEl.style.display = "block";
          tooltipEl.style.left = (event.pageX) + "px";
          tooltipEl.style.top = (event.pageY) + "px";
          tooltipEl.textContent = path + " – LOC: " + (d.value ?? 0);
        })
        .on("mouseleave", () => {
          tooltipEl.style.display = "none";
        });

      function focusOn(d) {
        currentNode = d;
        const xDomain = [d.x0, d.x1];
        const yDomain = [d.y0, radius];
        const xd = d3.scaleLinear().domain(xDomain).range([0, 2 * Math.PI]);
        const yd = d3.scaleLinear().domain(yDomain).range([0, radius]);

        nodes.transition().duration(750).attrTween("d", node => {
          const i = d3.interpolate(
            { x0: node.x0, x1: node.x1, y0: node.y0, y1: node.y1 },
            {
              x0: Math.max(0, Math.min(1, (node.x0 - d.x0) / (d.x1 - d.x0))) * 2 * Math.PI,
              x1: Math.max(0, Math.min(1, (node.x1 - d.x0) / (d.x1 - d.x0))) * 2 * Math.PI,
              y0: Math.max(0, node.y0 - d.y0),
              y1: Math.max(0, node.y1 - d.y0),
            }
          );
          return t => {
            const b = i(t);
            return d3.arc()
              .startAngle(b.x0)
              .endAngle(b.x1)
              .innerRadius(b.y0)
              .outerRadius(b.y1)();
          };
        });
        updateBreadcrumbs(d);
      }

      focusOn(root);
    } else {
      const treemap = d3.treemap()
        .size([width, height])
        .padding(1);
      treemap(root);

      const nodes = svg.selectAll("g.node")
        .data(root.descendants())
        .join("g")
        .attr("class", "node")
        .attr("transform", d => `translate(${d.x0},${d.y0})`)
        .on("click", (event, d) => {
          currentNode = d;
          updateBreadcrumbs(d);
          checks.clickZoom = true;
        })
        .on("mousemove", (event, d) => {
          const path = d.ancestors().reverse().map(x => x.data.name).join("/");
          tooltipEl.style.display = "block";
          tooltipEl.style.left = (event.pageX) + "px";
          tooltipEl.style.top = (event.pageY) + "px";
          tooltipEl.textContent = path + " – LOC: " + (d.value ?? 0);
        })
        .on("mouseleave", () => {
          tooltipEl.style.display = "none";
        });

      nodes.append("rect")
        .attr("fill", d => color(d.height))
        .attr("width", d => Math.max(0, d.x1 - d.x0))
        .attr("height", d => Math.max(0, d.y1 - d.y0));

      nodes.append("text")
        .attr("dx", 3)
        .attr("dy", 10)
        .text(d => d.data.name)
        .attr("font-size", "9px")
        .attr("pointer-events", "none");

      updateBreadcrumbs(root);
    }

    checks.rendered = true;

    function updateBreadcrumbs(node) {
      const path = node.ancestors().reverse();
      breadcrumbsEl.innerHTML = "";
      path.forEach((d, i) => {
        const span = document.createElement("span");
        span.textContent = d.data.name || "(root)";
        span.onclick = () => {
          currentNode = d;
          updateBreadcrumbs(d);
        };
        breadcrumbsEl.appendChild(span);
      });
      checks.breadcrumbs = true;
    }

    const searchInput = document.getElementById("q3-search");
    const searchInfo = document.getElementById("q3-search-info");
    searchInput.addEventListener("keydown", (e) => {
      if (e.key !== "Enter") return;
      const term = searchInput.value.trim().toLowerCase();
      if (!term) return;
      const matches = root.descendants().filter(d => (d.data.name || "").toLowerCase().includes(term));
      if (!matches.length) {
        searchInfo.textContent = "No matches";
        return;
      }
      searchInfo.textContent = `${matches.length} match(es)`;
      const first = matches[0];
      checks.search = true;

      const pathSet = new Set(first.ancestors());

      d3.selectAll("#q3-svg path, #q3-svg rect").style("stroke", null).style("stroke-width", null).style("opacity", 0.3);

      d3.selectAll("#q3-svg path, #q3-svg rect")
        .filter(function (d) { return pathSet.has(d); })
        .style("opacity", 1)
        .style("stroke", "#ff9800")
        .style("stroke-width", 2);

      updateBreadcrumbs(first);
    });

    const failures = Object.entries(checks).filter(([, v]) => !v).map(([k]) => k);
    if (failures.length === 0) {
      appendStatus(qid + ": PASS");
      summary[qid] = "PASS";
    } else {
      appendStatus(qid + ": FAIL – " + failures.join(", "));
      summary[qid] = "FAIL";
    }
    setSummaryAndMaybeRenderBox();
  } catch (err) {
    console.error(qid + " error:", err);
    appendStatus(qid + ": FAIL – " + err.message);
    summary[qid] = "FAIL";
    setSummaryAndMaybeRenderBox();
  }
}

function generateData() {
  return Array.from({ length: 10 }, () => ({
    id: crypto.randomUUID(),
    value: Math.random() * 100
  }));
}

async function initQ4() {
  const qid = "Q4";
  appendStatus(qid + ": initializing…");
  const checks = {
    ticking: false,
    enterUpdateExit: false,
    sorted: false,
    scrolling: false,
    pauseResume: false,
    threshold: false,
  };
  try {
    const barSvg = d3.select("#q4-bars-svg");
    const lineSvg = d3.select("#q4-line-svg");
    barSvg.selectAll("*").remove();
    lineSvg.selectAll("*").remove();

    const barW = +barSvg.attr("width");
    const barH = +barSvg.attr("height");
    const lineW = +lineSvg.attr("width");
    const lineH = +lineSvg.attr("height");
    const margin = { top: 10, right: 20, bottom: 24, left: 40 };
    const innerBarH = barH - margin.top - margin.bottom;
    const innerBarW = barW - margin.left - margin.right;
    const innerLineH = lineH - margin.top - margin.bottom;
    const innerLineW = lineW - margin.left - margin.right;

    const barG = barSvg.append("g").attr("transform", `translate(${margin.left},${margin.top})`);
    const lineG = lineSvg.append("g").attr("transform", `translate(${margin.left},${margin.top})`);

    const xBar = d3.scaleBand().padding(0.1).range([0, innerBarW]);
    const yBar = d3.scaleLinear().domain([0, 100]).range([innerBarH, 0]);
    const xLine = d3.scaleLinear().domain([0, 50]).range([0, innerLineW]);
    const yLine = d3.scaleLinear().domain([0, 100]).range([innerLineH, 0]);

    barG.append("g")
      .attr("class", "x-axis")
      .attr("transform", `translate(0,${innerBarH})`);
    barG.append("g")
      .attr("class", "y-axis")
      .call(d3.axisLeft(yBar));

    lineG.append("g")
      .attr("class", "x-axis-line")
      .attr("transform", `translate(0,${innerLineH})`)
      .call(d3.axisBottom(xLine).ticks(5));
    lineG.append("g")
      .attr("class", "y-axis-line")
      .call(d3.axisLeft(yLine));

    const clipId = "q4-line-clip";
    lineSvg.append("defs").append("clipPath")
      .attr("id", clipId)
      .append("rect")
      .attr("width", innerLineW)
      .attr("height", innerLineH);

    const linePathG = lineG.append("g")
      .attr("clip-path", `url(#${clipId})`);

    const lineGen = d3.line()
      .x((d, i) => xLine(i))
      .y(d => yLine(d));

    let history = [];
    let currentData = generateData();
    let running = true;

    const toggleBtn = document.getElementById("q4-toggle");
    const thresholdInput = document.getElementById("q4-threshold");
    const thresholdValue = document.getElementById("q4-threshold-value");
    const statusText = document.getElementById("q4-status-text");
    const meanText = document.getElementById("q4-mean");

    function updateBars(data) {
      data.sort((a, b) => d3.descending(a.value, b.value));
      xBar.domain(data.map((d, i) => i));

      const bars = barG.selectAll("rect.bar")
        .data(data, d => d.id);

      const threshold = +thresholdInput.value;

      const barsEnter = bars.enter().append("rect")
        .attr("class", "bar")
        .attr("x", innerBarW)
        .attr("width", xBar.bandwidth())
        .attr("y", innerBarH)
        .attr("height", 0)
        .attr("fill", d => d.value >= threshold ? "red" : "#90caf9");

      barsEnter.merge(bars)
        .transition().duration(600)
        .attr("x", (d, i) => xBar(i))
        .attr("y", d => yBar(d.value))
        .attr("height", d => innerBarH - yBar(d.value))
        .attr("width", xBar.bandwidth())
        .attr("fill", d => d.value >= threshold ? "red" : "#90caf9");

      bars.exit()
        .transition().duration(400)
        .attr("y", innerBarH)
        .attr("height", 0)
        .style("opacity", 0)
        .remove();

      barG.select(".x-axis").transition().call(d3.axisBottom(xBar).tickFormat(""));

      checks.enterUpdateExit = true;
      checks.sorted = true;
      checks.threshold = true;
    }

    function updateLine(mean) {
      if (!Number.isFinite(mean)) return;
      history.push(mean);
      const maxPoints = 50;
      if (history.length > maxPoints) {
        history = history.slice(history.length - maxPoints);
      }
      const data = history.slice();
      xLine.domain([0, maxPoints - 1]);
      yLine.domain([0, 100]);

      const lineSel = linePathG.selectAll("path").data([data]);
      lineSel.enter().append("path")
        .attr("fill", "none")
        .attr("stroke", "#ff6f00")
        .attr("stroke-width", 1.5)
        .merge(lineSel)
        .transition().duration(600)
        .attr("d", lineGen);

      lineSel.exit().remove();
      checks.scrolling = true;
    }

    function tick() {
      if (!running) return;
      checks.ticking = true;
      currentData = generateData();
      const mean = d3.mean(currentData, d => d.value) ?? 0;
      meanText.textContent = mean.toFixed(1);
      updateBars(currentData);
      updateLine(mean);
    }

    toggleBtn.addEventListener("click", () => {
      running = !running;
      toggleBtn.textContent = running ? "Pause" : "Resume";
      statusText.textContent = running ? "Running" : "Paused";
      checks.pauseResume = true;
    });

    thresholdInput.addEventListener("input", () => {
      thresholdValue.textContent = thresholdInput.value;
      updateBars(currentData);
    });

    tick();
    const interval = setInterval(() => {
      if (!document.body.contains(barSvg.node())) {
        clearInterval(interval);
        return;
      }
      tick();
    }, 2000);

    setTimeout(() => {
      const failures = Object.entries(checks).filter(([, v]) => !v).map(([k]) => k);
      if (failures.length === 0) {
        appendStatus(qid + ": PASS");
        summary[qid] = "PASS";
      } else {
        appendStatus(qid + ": FAIL – " + failures.join(", "));
        summary[qid] = "FAIL";
      }
      setSummaryAndMaybeRenderBox();
    }, 6500);
  } catch (err) {
    console.error(qid + " error:", err);
    appendStatus(qid + ": FAIL – " + err.message);
    summary[qid] = "FAIL";
    setSummaryAndMaybeRenderBox();
  }
}

(async function main() {
  appendStatus("Initializing visualizations…");
  await initQ1();
  await initQ2();
  await initQ3();
  await initQ4();
})();
