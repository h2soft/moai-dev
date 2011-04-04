::kill existing copy of source files folder, if any
if exist src-copy rmdir /s /q src-copy

::create copy of source files
xcopy /v /i /s /y "../src" "src-copy"

::modify copy of source files
call parser\process-files
pause
REM set PARAM_EXP_PREFIX=(\@name.*?\()(.*?)\s*?\).*?\@param
REM set PARAM_EXP_SUFFIX=\s*(\w*?)\s*?\@type\s*(\w*)(.*?)\n(.*?)\@return
REM set PARAM_EXP_REPLACE=$1 $2, $3 \)\n$6\@param $3 \($4\) $5\n\t\@return

REM call parser\fr "src-copy" "*" "(\@name\s*?(\w*?))\n" "$1 \(\)\n"
REM call parser\fr "src-copy" "*" "%PARAM_EXP_PREFIX%1%PARAM_EXP_SUFFIX%" "%PARAM_EXP_REPLACE%"
REM call parser\fr "src-copy" "*" "%PARAM_EXP_PREFIX%2%PARAM_EXP_SUFFIX%" "%PARAM_EXP_REPLACE%"
REM call parser\fr "src-copy" "*" "%PARAM_EXP_PREFIX%3%PARAM_EXP_SUFFIX%" "%PARAM_EXP_REPLACE%"
REM call parser\fr "src-copy" "*" "%PARAM_EXP_PREFIX%4%PARAM_EXP_SUFFIX%" "%PARAM_EXP_REPLACE%"
REM call parser\fr "src-copy" "*" "%PARAM_EXP_PREFIX%5%PARAM_EXP_SUFFIX%" "%PARAM_EXP_REPLACE%"
REM call parser\fr "src-copy" "*" "%PARAM_EXP_PREFIX%6%PARAM_EXP_SUFFIX%" "%PARAM_EXP_REPLACE%"
REM call parser\fr "src-copy" "*" "%PARAM_EXP_PREFIX%7%PARAM_EXP_SUFFIX%" "%PARAM_EXP_REPLACE%"
REM call parser\fr "src-copy" "*" "%PARAM_EXP_PREFIX%8%PARAM_EXP_SUFFIX%" "%PARAM_EXP_REPLACE%"
REM call parser\fr "src-copy" "*" "%PARAM_EXP_PREFIX%9%PARAM_EXP_SUFFIX%" "%PARAM_EXP_REPLACE%"
REM call parser\fr "src-copy" "*" " , " ", "
REM call parser\fr "src-copy" "*" "(\@name.*?\() ,(.*?)\)" "$1$2\)"
REM call parser\fr "src-copy" "*" "\@name\s*?(\w*?.*?)\)" "\@brief\n\t\<tt\>function$1\)\<\/tt\>\\n\n\t\\n"
REM call parser\fr "src-copy" "*" "\@text\s*(\w{1}.*?)\n" "$1\n"
REM call parser\fr "src-copy" "*" "(\@return.*?)(\w{1}.*?)\@type\s*?(\w*?)\n" "$1$2\($3\)\n"

::kill existing doxygen output folder, if any
rmdir /s /q html-lua

::run doxygen on copy of source files
doxygen doxyfile-lua

::modify doxygen's output
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
call parser\fr "html-lua" "*.html" "(\>)_(.*?\(\))" "$1$2"
