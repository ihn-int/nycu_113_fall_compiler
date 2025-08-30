# hw3 report

|      |           |
| ---: | :-------- |
| Name | 陳均凱     |
|   ID | 111550001 |

## How much time did you spend on this project

> e.g. 2 hours.

不包含寫結報的時間，大約花了整整三天（36 小時的意思。）

## Project overview

> Please describe the structure of your code and the ideas behind your implementation in an organized way.
> The point is to show us how you deal with the problems. It is not necessary to write a lot of words or paste all of your code here.

考量到作業的 repo 裡面本來就有提供 visitor pattern 的 hint ， guideline 也有說明每個節點需要包含的資訊以及該節點的類別。依照這兩份文件提供的資訊，作業的大部分內容都可以完成。除了 scanner 程式當中需要修改的部分，缺了這部分會導致 yacc 的 parser 處理常數時發生問題，內容和型別都會。

雖然可以從測資開始一筆一筆進行進而完成整份作業，不過我當時是先完成整個 AST 的 library 後才修改 parser 的，儘管看上去是個折衷的作法，卻還是遇到不少編譯錯誤（是我花了這麼多時間的原因之一）。此時就必須從 parser 給出的結果比對 sample solution 而推測出問題可能的地方，再予以修改。

程式內容有不少東西都是為了因應執行期間錯誤而添加的修改，雖然有在完成後試著將 library 和 parser 整理得乾淨一些，在檢閱原始碼時如果有看到某些奇怪的 new 或是亂七八糟的 header file 基本上是出自這個原因。

另外，我一開始建立 AST 時並沒有依照 visitor pattern 的 hint 為每個結點在 union 中建立對應的指標（我覺得會過於冗長），而全部使用 `AstNode` 類別，不過後來又在轉型和物件存取上遇到困難，最後還是放棄這個想法，使用 hint 中的方法建立 AST 。我也有試著使用 string value 作為 constant value 的儲存方式，不過也在轉型等方面遇到問題，這個做法也被放棄。

## What is the hardest you think in this project

> Not required, but bonus point may be given.

自從我考過 GPE 後，OOP 和 DS 就還給老師了，也較少使用 C++ ，所以作業困難的地方圍繞這部分。例如說，現代的 C++ 會追蹤物件的使用情況，在離開有效範圍後物件會被回收。如果有某個節點或字串以物件的方式生成，可能會在錯誤的使用下讓指標的存取失效。又或是在執行 Destructor 時，試圖刪除已經刪除的節點。後來我才把物件都用動態分配，並且使用預設的 Destructor 。

## Feedback to T.A.s

> Not required, but bonus point may be given.

好難，不過給的文件都很有幫助。