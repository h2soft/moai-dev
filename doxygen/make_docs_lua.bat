::kill existing copy of source files folder, if any
if exist src-copy rmdir /s /q src-copy

::create copy of source files
xcopy /v /i /s /y "../src" "src-copy"

::modify copy of source files
call parser\process-files

::kill existing doxygen output folder, if any
rmdir /s /q html-lua

::run doxygen on copy of source files
doxygen doxyfile-lua

::modify doxygen's output

set /p introPage= <intro-page.txt

::proper escape file
copy /y intro-page.txt intro-page-temp.txt
call parser\fr "." "intro-page-temp.txt" "([\<\>\"\"\&\/\\\;\.\'\'\:])" "\\$1"

::load contents of intro text file
setlocal ENABLEDELAYEDEXPANSION
set input=
for /F "tokens=*" %%i in (intro-page-temp.txt) do (
	set input=!input!\n%%i
)
del /q intro-page-temp.txt

call parser\fr "html-lua" "index.html" "(\<div class=\"contents\"\>).*?(\<\/div\>)" "$1%input%$2"

call parser\fr "html-lua" "*.html" "Static .*? Member Functions" "Function List"
call parser\fr "html-lua" "*.html" "Member Function Documentation" "Function Documentation"
call parser\fr "html-lua" "*.html" "SUPPRESS_EMPTY_FILE_WARNING" ""
call parser\fr "html-lua" "*.html" "static int(.*?\>)_(.*?\<\/a\>)" "$1$2"
call parser\fr "html-lua" "*.html" "\(lua_State \*L\)" ""
call parser\fr "html-lua" "*.html" "int MOAI.*?::_(.*?\<\/td\>)" "$1"
call parser\fr "html-lua" "*.html" "(\>)lua_State \*.*?(\<)" "$1$2"
call parser\fr "html-lua" "*.html" "\<em\>L\<\/em\>" ""
call parser\fr "html-lua" "*.html" "\<td class=\"paramtype\"\>\<\/td\>" ""
call parser\fr "html-lua" "*.html" "\<td class=\"paramname\"\>\<\/td\>" ""
call parser\fr "html-lua" "*.html" "\<td\>\(\<\/td\>" ""
call parser\fr "html-lua" "*.html" "\<td\>\)\<\/td\>" ""
call parser\fr "html-lua" "*.html" "\[.*?static.*?\]" ""
call parser\fr "html-lua" "*.html" "(\>)_(.*?\<\/a\>)" "$1$2"

endlocal