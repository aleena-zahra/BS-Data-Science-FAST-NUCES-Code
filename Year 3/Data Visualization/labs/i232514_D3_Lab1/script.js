// Part 1


d3.select("h2")
    .style("color", "pink")
    .style("font-size", "30px");

d3.select("body")
    .append("p")
    .text("Das ist mein erster Absatz.")
    .style("color", "red");

d3.select("body")
    .append("p")
    .text("Das ist mein zweiter Absatz.")
    .style("color", "orange");

d3.select("body")
    .append("p")
    .text("Das ist mein dritter Absatz.")
    .style("color", "purple");


// Part 2

const data = [2, 5, 40, 15, 70, 45];

const container = d3.select("#container");

container
    .selectAll("p")
    .data(data)
    .enter()
    .append("p")
    .text(d => `${d}`)
    .style("color", d => d > 30 ? "purple" : "black");

// Part 3
const svg = d3.select("body")
    .append("svg")
    .attr("width", 500)
    .attr("height", 300)
    .style("border", "2px solid lightblue");


svg.append("circle")
    .attr("cx", 200)
    .attr("cy", 80)
    .attr("r", 36)
    .attr("fill", "pink");
svg.append("rect")
    .attr("x", 30)
    .attr("y", 30)
    .attr("width", 100)
    .attr("height", 260)
    .attr("fill", "lightgreen");
svg.append("line")
    .attr("x1", 300)
    .attr("y1", 20)
    .attr("x2", 380)
    .attr("y2", 300)
    .attr("stroke", "black")
    .attr("stroke-width", 2);

// Part 4
const barWidth = 30;
const barSpacing = 10;

svg2 = d3.select("body")
    .append("svg")
    .attr("width", 250)
    .attr("height", 150)
    .style("border", "2px solid lightblue");


svg2.selectAll("rect.bar")
    .data(data)
    .enter()
    .append("rect")
    .attr("class", "bar")
    .attr("x", (d, i) => 10 + i * (barWidth + barSpacing))
    .attr("y", d => 100 - d)
    .attr("width", barWidth)
    .attr("height", d => d)
    .attr("fill", "blue");

svg2.selectAll("text.label")
    .data(data)
    .enter()
    .append("text")
    .attr("class", "label")
    .attr("x", (d, i) => 20 + i * (barWidth + barSpacing) + barWidth / 2)
    .attr("y", d => 90 - d)
    .attr("text-anchor", "middle")
    .style("font-size", "10px")
    .text(d => d);

// Part 5

const yScale = d3.scaleLinear()
    .domain([0, d3.max(data)])
    .range([0, 200]);
svg3 = d3.select("body")
    .append("svg")
    .attr("width", 350)
    .attr("height", 300)
    .style("border", "2px solid orange");

svg3.selectAll("rect.scaled-bar")
    .data(data)
    .enter()
    .append("rect")
    .attr("class", "scaled-bar")
    .attr("x", (d, i) => 20 + i * (barWidth + barSpacing))
    .attr("y", d => 280 - yScale(d))
    .attr("width", barWidth)
    .attr("height", d => yScale(d))
    .attr("fill", "orange");
svg3.selectAll("text.label")
    .data(data)
    .enter()
    .append("text")
    .attr("class", "label")
    .attr("x", (d, i) => 20 + i * (barWidth + barSpacing) + barWidth / 2)
    .attr("y", d => 290)
    .attr("text-anchor", "middle")
    .style("font-size", "10px")
    .text(d => d);

// Part 6
const scatterData = [
    { x: 30, y: 20 },
    { x: 70, y: 90 },
    { x: 110, y: 50 },
    { x: 160, y: 120 },
    { x: 220, y: 70 }
];

const xScale = d3.scaleLinear().domain([0, 250]).range([0, 300]);
const yScaleScatter = d3.scaleLinear().domain([0, 150]).range([150, 0]);
svg4 = d3.select("body")
    .append("svg")
    .attr("width", 350)
    .attr("height", 200)
    .style("border", "2px solid green");

svg4.selectAll("circle.point")
    .data(scatterData)
    .enter()
    .append("circle")
    .attr("class", "point")
    .attr("cx", d => xScale(d.x))
    .attr("cy", d => yScaleScatter(d.y))
    .attr("r", 6)
    .attr("fill", d => d.x > 100 ? "red" : "green");

svg4.selectAll("text.point-label")
    .data(scatterData)
    .enter()
    .append("text")
    .attr("class", "point-label")
    .attr("x", d => xScale(d.x) + 8)
    .attr("y", d => yScaleScatter(d.y) - 5)
    .style("font-size", "10px")
    .text(d => `(${d.x}, ${d.y})`);

// Part 7
const newData = [10, 25, 50, 35, 80, 60];

const colorScale = d3.scaleSequential(d3.interpolateReds)
    .domain([0, d3.max(newData)]);

svg3.selectAll("rect.scaled-bar")
    .data(newData)
    .transition()
    .duration(1000)
    .attr("y", d => 280 - yScale(d))
    .attr("height", d => yScale(d))
    .attr("fill", d => colorScale(d));

svg3.selectAll("text.label")
    .data(newData)
    .transition()
    .duration(1000)
    .text(d => d);

