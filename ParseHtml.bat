lemon lemon.html.yy
win_flex_bison-latest\win_flex -Phtml --outfile="lexer.html.cpp"  lexer.html.ll
copy /y lemon.html.c lemon.html.cpp

lemon -b lemon.pre.yy
win_flex_bison-latest\win_flex -Ppre --outfile="lexer.pre.cpp"  lexer.pre.ll
copy /y lemon.pre.c lemon.pre.cpp