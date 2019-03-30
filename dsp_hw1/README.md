# DSP HW1

> b05901011 許秉倫

## Analyze

1. 實測觀察後發現，在training的過程中，參數會逐漸朝向某個方向收斂，並且使得accuracy逐漸提升
2. 我在test1的accuracy最終大約為87%，可推知model訓練的結果應該算還不錯

## Execution

- Environment: macOS

- Makefile

  ```bash
  # enter my folder
  cd hw1_b05901011
  # compile train/test
  make
  # clean folder
  make clean
  ```

- Train

  ```bash
  ./train 1000 ../model_init.txt ../seq_model_01.txt ./model_01.txt
  ./train 1000 ../model_init.txt ../seq_model_02.txt ./model_02.txt
  ./train 1000 ../model_init.txt ../seq_model_03.txt ./model_03.txt
  ./train 1000 ../model_init.txt ../seq_model_04.txt ./model_04.txt
  ./train 1000 ../model_init.txt ../seq_model_05.txt ./model_05.txt
  ```

- Test

  ```bash
  ./test ../modellist.txt ../testing_data1.txt ../result1.txt
  ./test ../modellist.txt ../testing_data2.txt ../result2.txt
  ```


