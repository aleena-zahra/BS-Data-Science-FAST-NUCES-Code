# i23-2514-NLP-Assignment3

## Execution Instructions

1. Place `beauty.json`, `electronics.json`, `home_and_kitchen.json` in the **same folder** as this notebook (or update `DATA_DIR` in Cell 1).
2. Run all cells top-to-bottom: **`Kernel → Restart & Run All`**
3. Outputs are saved automatically:
   - `models/` — trained encoder & decoder weights
   - `results/` — embeddings, metrics, plots

## Dependencies
```
pip install torch numpy scikit-learn matplotlib tqdm
```

## System Overview
This notebook implements a three-stage NLP pipeline:

| Stage | Part | Model |
|-------|------|-------|
| A | Encoder | Encoder-only Transformer (multi-task: sentiment + review length class) |
| B | Retrieval | Cosine-similarity nearest-neighbour over saved embeddings |
| C | Decoder | Decoder-only Transformer (autoregressive explanation generation) |

This code is the implementation of Assignment 3 for the course of Natural Language Processing at FAST NUCES
