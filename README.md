# Pipex

42 School の課題として実装した Unix パイプの再現プログラムです。入力ファイル、2 つのコマンド、出力ファイルを受け取り、シェルのパイプ処理を C で実装しています。

## 概要

- 出力物: `pipex`
- Mandatory: 2 コマンドのパイプ接続
- Bonus: 複数コマンドのチェーン接続
- 実装要素: `fork`, `pipe`, `dup2`, `execve`, `PATH` 解決

## 使用例

```bash
./pipex infile "grep hello" "wc -l" outfile
./pipex infile "cmd1" "cmd2" outfile
```

シェルでは次と同等です。

```bash
< infile grep hello | wc -l > outfile
```

## ビルド

```bash
make
make bonus
make clean
make fclean
make re
```

## 実装メモ

- エラー時のファイルディスクリプタとメモリ解放を整理
- 実行可能ファイルを `PATH` から検索
- bonus 版ではコマンド数を増やしても同じ流れで処理
