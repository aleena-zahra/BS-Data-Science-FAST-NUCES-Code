
# app.py — CardioAI Heart Disease Risk Dashboard
# Run: streamlit run app.py

import streamlit as st
import numpy as np
import pandas as pd
import joblib
import json
import shap
import matplotlib.pyplot as plt
from pathlib import Path

# ── Load model and metadata 
BASE_DIR = Path(__file__).resolve().parent

model   = joblib.load(BASE_DIR / 'models' / 'best_model.pkl')
scaler  = joblib.load(BASE_DIR / 'models' / 'scaler.pkl')
with open(BASE_DIR / 'data' / 'feature_meta.json') as f:
    meta = json.load(f)

CONT_COLS = meta['cont_cols']
FEATURE_NAMES = meta['feature_names']

# ── Demo patient (pre-populated form) 
DEMO = dict(age=63, sex=1, cp=1, trestbps=145, chol=233,
            fbs=1, restecg=2, thalach=150, exang=0,
            oldpeak=2.3, slope=3, ca=0, thal=6)

st.set_page_config(page_title="CardioAI — Heart Disease Risk", layout="wide")
st.title("🫀 CardioAI — Heart Disease Risk Predictor")
st.markdown("Screening support tool for community cardiologists. "
            "Enter patient measurements below and click **Predict**.")

# ── E1: Input form 
with st.form(key="patient_form"):
    st.subheader("Patient Features")
    col1, col2, col3 = st.columns(3)

    with col1:
        age      = st.number_input("Age (20–80)",      20, 80,  DEMO["age"])
        sex      = st.selectbox("Sex (1=Male, 0=Female)", [1, 0], index=0)
        cp       = st.selectbox("Chest Pain Type cp (1–4)", [1, 2, 3, 4],
                                 index=0 if DEMO["cp"] <= 0 else int(DEMO["cp"]) - 1)
        trestbps = st.number_input("Resting BP trestbps (90–200 mmHg)", 90, 200, DEMO["trestbps"])
        chol     = st.number_input("Cholesterol chol (100–600 mg/dl)",   100, 600, DEMO["chol"])

    with col2:
        fbs     = st.selectbox("Fasting Blood Sugar > 120 mg/dl fbs (0/1)", [0, 1], index=int(DEMO["fbs"]))
        restecg = st.selectbox("Resting ECG restecg (0–2)", [0, 1, 2], index=int(DEMO["restecg"]))
        thalach = st.number_input("Max Heart Rate thalach (70–210)", 70, 210, DEMO["thalach"])
        exang   = st.selectbox("Exercise-Induced Angina exang (0/1)", [0, 1], index=int(DEMO["exang"]))

    with col3:
        oldpeak = st.number_input("ST Depression oldpeak (0.0–6.2)", 0.0, 6.2, float(DEMO["oldpeak"]), step=0.1)
        slope   = st.selectbox("ST Slope slope (1–3)", [1, 2, 3], index=max(0, int(DEMO["slope"]) - 1))
        ca      = st.number_input("Major Vessels ca (0–3)",  0, 3, DEMO["ca"])
        thal    = st.selectbox("Thalassemia thal (3=Normal, 6=Fixed, 7=Reversible)", [3, 6, 7],
                                index=0 if int(DEMO["thal"]) not in [3, 6, 7] else [3, 6, 7].index(int(DEMO["thal"])))

    submitted = st.form_submit_button("Predict")

# ── E2: Results panel
if submitted:
    raw = pd.DataFrame([dict(age=age, sex=sex, cp=cp, trestbps=trestbps,
                              chol=chol, fbs=fbs, restecg=restecg,
                              thalach=thalach, exang=exang, oldpeak=oldpeak,
                              slope=slope, ca=ca, thal=thal)])

    cat_cols = ["cp", "restecg", "slope", "thal"]
    raw[cat_cols] = raw[cat_cols].astype(float)
    raw_enc = pd.get_dummies(raw, columns=cat_cols, drop_first=False)

    # Align to training feature columns
    for col in FEATURE_NAMES:
        if col not in raw_enc:
            raw_enc[col] = 0
    raw_enc = raw_enc[FEATURE_NAMES]

    # Scale continuous columns
    raw_enc[CONT_COLS] = scaler.transform(raw_enc[CONT_COLS])

    prob = model.predict_proba(raw_enc)[0][1]
    pred = int(prob >= 0.5)

    st.markdown("---")
    st.subheader("Prediction Result")

    if pred == 1:
        st.error(f"Disease Present — Confidence: {prob*100:.1f}%")
    else:
        st.success(f"No Disease — Confidence: {(1-prob)*100:.1f}%")

    # SHAP top-3 features
    explainer = shap.TreeExplainer(model)
    sv = explainer.shap_values(raw_enc)
    shap_series = pd.Series(sv[0], index=FEATURE_NAMES).abs().sort_values(ascending=False)
    top3 = shap_series.head(3)

    fig, ax = plt.subplots(figsize=(5, 2.5))
    top3.sort_values().plot(kind="barh", ax=ax, color="steelblue", edgecolor="k")
    ax.set_title("Top 3 Driving Features (|SHAP|)", fontsize=10)
    ax.set_xlabel("Absolute SHAP Value")
    st.pyplot(fig)

    top_feat = top3.index[0]
    st.markdown(
        f"**Clinical note:** This patient's **{top_feat}** value is the strongest indicator "
        f"of {'elevated cardiac risk' if pred==1 else 'low cardiac risk'}. "
        "The top-3 features highlighted above are the most influential measurements "
        "in this prediction. A follow-up ECG and stress test are recommended if the model "
        "flags disease risk, particularly when oldpeak and thalach are in abnormal ranges."
    )
