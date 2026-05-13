const YEAR_START = 1900;
const YEAR_END = 2021;

const fuelAliases = new Map([
  ["Natural Gas", "Gas"],
  ["Oil", "Oil"],
  ["Petroleum", "Oil"],
  ["Other", "Other"],
]);

const renewableFuels = new Set([
  "Solar",
  "Wind",
  "Hydro",
  "Geothermal",
  "Biomass",
  "Waste",
  "Storage",
]);

const parseNumber = (value) => {
  const num = +value;
  return Number.isFinite(num) ? num : null;
};

const normalizeFuel = (fuel) => {
  if (!fuel) return "Other";
  const trimmed = fuel.trim();
  if (fuelAliases.has(trimmed)) {
    return fuelAliases.get(trimmed);
  }
  return trimmed;
};

export async function loadTask1Data() {
  const [plantsRaw, world] = await Promise.all([
    d3.csv("database_WRI.csv"),
    d3.json("world.geojson"),
  ]);

  const plants = plantsRaw
    .map((d) => ({
      id: d.gppd_idnr,
      name: d.name,
      countryCode: d.country,
      countryName: d.country_long,
      capacity: parseNumber(d.capacity_mw) ?? 0,
      latitude: d.latitude?.trim() === "" ? null : parseNumber(d.latitude),
      longitude: d.longitude?.trim() === "" ? null : parseNumber(d.longitude),
      primaryFuel: normalizeFuel(d.primary_fuel),
      commissioningYear: parseNumber(d.commissioning_year),
    }))
    .filter((d) => Number.isFinite(d.latitude) && Number.isFinite(d.longitude));

  const countryCentroids = new Map();
  const geoPath = d3.geoPath();
  world.features.forEach((feature) => {
    const props = feature.properties;
    const iso =
      feature.id ||
      props.ISO_A3 ||
      props.iso_a3 ||
      props.ADM0_A3 ||
      props.ADMIN ||
      props.NAME;

    if (!iso) return;

    countryCentroids.set(iso.toUpperCase(), geoPath.centroid(feature));
  });


  return {
    plants,
    world,
    countryCentroids,
    renewableFuels,
  };
}

const columnYears = (row) =>
  Object.keys(row)
    .filter((key) => /^\d{4}$/.test(key))
    .map((key) => +key);

const clampYearRange = (year) =>
  Math.max(YEAR_START, Math.min(YEAR_END, year));

export async function loadTask2Data() {
  const [gdpRaw, lifeRaw, popRaw, isoMeta, world] = await Promise.all([
    d3.csv("gdp_pcap.csv"),
    d3.csv("lex.csv"),
    d3.csv("pop.csv"),
    d3.json("iso_regions.json"),
    d3.json("world.geojson"),
  ]);

  const years = columnYears(gdpRaw[0])
    .map(clampYearRange)
    .filter((year) => year >= YEAR_START && year <= YEAR_END);

  const metaByIso3 = new Map();
  isoMeta.forEach((entry) => {
    metaByIso3.set(entry["alpha-3"], {
      name: entry.name,
      region: entry.region || entry["sub-region"] || "Other",
      subRegion: entry["sub-region"] || "Other",
      continent: entry.region || "Other",
    });
  });

  const byIso = new Map();
  const ingestSeries = (rows, key) => {
    rows.forEach((row) => {
      const iso = row.geo?.toUpperCase();
      if (!iso) return;
      if (!byIso.has(iso)) {
        byIso.set(iso, { iso, name: row.name });
      }
      const record = byIso.get(iso);
      if (!record[key]) {
        record[key] = new Map();
      }
      years.forEach((year) => {
        const val = parseNumber(row[year]);
        if (Number.isFinite(val)) {
          record[key].set(year, val);
        }
      });
    });
  };

  ingestSeries(gdpRaw, "gdp");
  ingestSeries(lifeRaw, "life");
  ingestSeries(popRaw, "pop");

  const rowsByYear = new Map();

  years.forEach((year) => {
    const rows = [];
    byIso.forEach((record) => {
      const gdp = record.gdp?.get(year);
      const life = record.life?.get(year);
      const pop = record.pop?.get(year);
      if (!Number.isFinite(gdp) || !Number.isFinite(life) || !Number.isFinite(pop)) {
        return;
      }
      const meta = metaByIso3.get(record.iso) || {
        continent: "Other",
        region: "Other",
        name: record.name,
      };

      rows.push({
        iso: record.iso,
        name: record.name,
        continent: meta.continent || meta.region || "Other",
        gdp,
        life,
        pop,
        year,
      });
    });
    rowsByYear.set(year, rows);
  });

  const continents = Array.from(
    new Set(
      Array.from(rowsByYear.values())
        .flat()
        .map((d) => d.continent)
    )
  ).sort();

  return {
    world,
    years,
    rowsByYear,
    metaByIso3,
    continents,
  };
}

