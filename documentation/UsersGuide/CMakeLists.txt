# -*- mode: CMAKE; explicit-buffer-name: "CMakeLists.txt<UsersGuide>" -*-

               set ( htmlInstallDir  share/doc/coriolis2/en/html/users-guide )
               set ( latexInstallDir share/doc/coriolis2/en/latex/users-guide )

 add_custom_target ( doc_HTML ALL
                        cd ${DOCUMENTATION_SOURCE_DIR}/UsersGuide
                     && rst2html --link-stylesheet --stylesheet=./SoC.css,./Pygments.css UsersGuide_HTML.rst UsersGuide.html )
  add_dependencies ( doc_HTML SoC.css Pygments.css UsersGuide_HTML.rst UsersGuide.rst )

 add_custom_target ( doc_LaTeX  ALL
                        cd ${DOCUMENTATION_SOURCE_DIR}/UsersGuide
                     && rst2latex --use-latex-toc --stylesheet=./socstyle.tex UsersGuide_LaTeX.rst UsersGuide-raw.tex
                     && sed 's, \\& \\\\multicolumn{2}{l|}{,  \\& \\\\multicolumn{2}{p{0.6\\\\DUtablewidth}|}{,' UsersGuide-raw.tex > UsersGuide.tex
                     && latex UsersGuide
                     && latex UsersGuide
                     && latex UsersGuide
                     && dvipdfm UsersGuide
                   )
  add_dependencies ( doc_HTML socstyle.tex UsersGuide_LaTeX.rst UsersGuide.rst )

           install ( DIRECTORY images/
                               DESTINATION ${htmlInstallDir}/images
                               FILES_MATCHING PATTERN "*.png" )
           install ( FILES     SoC.css
                               Pygments.css
                               UsersGuide.html      DESTINATION ${htmlInstallDir} )

           install ( DIRECTORY images/
                               DESTINATION ${latexInstallDir}/images
                               FILES_MATCHING PATTERN "*.pdf"
                                              PATTERN "*.eps"
                                              PATTERN "*.bb" )

           install ( FILES     socstyle.tex
                               UsersGuide.tex       DESTINATION ${latexInstallDir} )
