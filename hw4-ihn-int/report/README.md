# hw4 report

|    |         |
| -: |:-       |
|Name|陳均凱    |
| ID |111550001|

## How much time did you spend on this project

> e.g. 2 hours.

我花了大約 30 小時完成這份作業。

## Project overview

> Please describe the structure of your code and the ideas behind your implementation in an organized way.
> The point is to show us how you deal with the problems. It is not necessary to write a lot of words or paste all of your code here.

完成作業的流程基本上是先釐清 symbol table 的設計，包含如何管理 table 。了解 table 後開始設計 `SymbolTable.[hc]pp` 。

接下來我是依照 `SemanticAnalyzer` 的函式順序逐步完成整個語法分析。有不少 test case 混雜多個語法，因此在完成所有內容之前，很少有某個 test case 有通過。不過我還是透過 result 的結果確認自己的 table 管理和物件存取有沒有出錯。

實作 `SemanticAnalyzer` 的過程中還有一些必須要處理的條件，例如要判斷目前的 compound statement 是否為函式的一部分，或是知道目前取得的變數視野是否為在 loop 內，都必須使用額外的變數記錄下來。

完成之後還是有遇到 test case 未通過的問題，此時才依據 simple solution 比對兩者差異，找到問題是出在 dump 還是 tabel 管理上。因為驗證結果是透過 diff 工具產生，所以連沒有列印出來的空格也會列入錯誤，這個問題可花了不少時間發現。

## What is the hardest you think in this project

> Not required, but bonus point may be given.

我在處理語法錯誤時有遇到一個滿有趣的問題：如果有某個運算式出現錯誤（例如運算元的型別錯誤），這個運算式的型別就不能被確定（我的實作裡面，必須要確定型別才會透過 `set()` 函式賦予型別，否則為 `nullptr`），此時任何一個會參考這個運算式結果的結構，例如 assignment 或是 array reference 都會因為索取到 nullptr 。我目前的作法會跳過這些 `nullptr` 。不確定是不是正確做法，不過 open case 目前都有通過。

## Feedback to T.A.s

> Not required, but bonus point may be given.

好難。