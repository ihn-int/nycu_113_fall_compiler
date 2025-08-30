# hw5 report

|||
|-:|:-|
|Name|陳均凱|
|ID|111550001|

## How much time did you spend on this project

> e.g. 2 hours.

大約 30 小時。

## Project overview

> Please describe the structure of your code and the ideas behind your implementation in an organized way.
> The point is to show us how you deal with the problems. It is not necessary to write a lot of words or paste all of your code here.

要完成整份 code 必須要先釐清如何模擬一個處理器的運作。以往計算機組織學到處理器架構都是基本的 register-register model ，代表運算源都來自暫存器。此次作業的範例則採用 stack model ，即運算元都來自於 stack 頂端。這點導致有不少指令其實耗費在「取得位址」、「push 或 pop stack」上。

針對不同類型的敘述式要妥善的處理對 stack 的操作，此外，也必須有不同的走訪方式，例如針對 function 的走訪需要區分出 parameter list 和 function body ，此處又必須要處理參數和 symbol table 的問題。或是針對 if 敘述，必須考慮到沒有 else 敘述的情況。很多對 AST 的操作都有參考 `SemanticAnalyzer` 。

關於 bonus 的部分，由於實在沒有額外的時間，只有實作比較容易的 boolean 而已。

## What is the hardest you think in this project

> Not required, but bonus point may be given.

看懂 stack model 算是一個問題，不過另外一個不容忽視的問題應該是除錯。原本的流程應該是 compile -> assemble -> execute ，不過不確定原因，我在處理 compile 階段錯誤時的結果沒有被列印到 result 裡面，但是在 terminal 輸入指令是可以看到的。此外，整個 test 被包裝得太完整導致要從中找出執行時的資訊已進行除錯變得更難。

## Feedback to T.A.s

> Not required, but bonus point may be given.

說好的比前兩個作業簡單呢？
