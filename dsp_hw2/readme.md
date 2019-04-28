# DSP Homework2-1 Report
> b05901011 電機三 許秉倫
## 1. Execution and Environment
- Execution
```bash
bash 00_clean_all.sh
bash 01_run_HCopy.sh
bash 02_run_HCompV.sh
bash 03_training.sh
bash 04_testing.sh
```
- Environment: macOS

## 2. Run Baseline (40%)
<img src='assets/baseline.png' width='500px'>

## 3. Improve Accuracy (40%)
<img src='assets/improved.png' width='500px'>

## 4. Describe training process and accuracy (30%)
- Best
  - Number of states: 12
  - Gaussian mixtures: 5
  - iterations: 3
  - Corr: 97.47%, Acc: 96.66%
- How some changes effect the performance: 
<img src="assets/experiment.png" width="500px">