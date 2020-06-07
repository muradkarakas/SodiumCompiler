lemon lemon.html.yy
win_flex_bison-latest\win_flex -Phtml --outfile="lexer.html.c"  lexer.html.ll

lemon -b lemon.pre.yy
win_flex_bison-latest\win_flex -Ppre --outfile="lexer.pre.c"  lexer.pre.ll
