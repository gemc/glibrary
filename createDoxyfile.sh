#!/bin/zsh


# Purpose: creates a doxyfile using the doxygen -g command to get the latest doxygen goodies)
# The replace each line with the ones shown below

echo " Creating System Doxyfile "
doxygen -g &> /dev/null

cp Doxyfile DoxyfilePure

# add "backup" to backup file on Mac. No need on Linux
extraArgument=''
case `uname` in
	Darwin)
		extraArgument='backup'
	;;
	Linux)
		extraArgument=''
	;;
esac

# painfully, manually doing these, but we HAVE TO
# Note: keep STRIP_CODE_COMMENTS (refers just to doxygen comments) and SOURCE_TOOLTIPS to yes to make browing more readable
sed -i $extraArgument 's/PROJECT_NAME           = "My Project"/PROJECT_NAME  = "templateGLibrary"/g'               Doxyfile
sed -i $extraArgument 's/REPEAT_BRIEF           = YES/REPEAT_BRIEF           = NO/g'                               Doxyfile
sed -i $extraArgument 's/OPTIMIZE_OUTPUT_FOR_C  = NO/OPTIMIZE_OUTPUT_FOR_C   = YES/g'                              Doxyfile
sed -i $extraArgument 's/BUILTIN_STL_SUPPORT    = NO/BUILTIN_STL_SUPPORT     = YES/g'                              Doxyfile
sed -i $extraArgument 's/SHOW_INCLUDE_FILES     = YES/SHOW_INCLUDE_FILES     = NO/g'                               Doxyfile
sed -i $extraArgument 's/SHOW_FILES             = YES/SHOW_FILES             = NO/g'                               Doxyfile
sed -i $extraArgument 's/SOURCE_BROWSER         = NO/SOURCE_BROWSER          = YES/g'                              Doxyfile
sed -i $extraArgument 's/RECURSIVE              = NO/RECURSIVE               = YES/g'                              Doxyfile
sed -i $extraArgument 's/HTML_COLORSTYLE_HUE    = 220/HTML_COLORSTYLE_HUE    = 200/g'                              Doxyfile
sed -i $extraArgument 's/HTML_COLORSTYLE_SAT    = 100/HTML_COLORSTYLE_SAT    = 240/g'                              Doxyfile
sed -i $extraArgument 's/HTML_COLORSTYLE_GAMMA  = 80/HTML_COLORSTYLE_GAMMA   = 190/g'                              Doxyfile
sed -i $extraArgument 's/HTML_DYNAMIC_MENUS     = YES/HTML_DYNAMIC_MENUS     = YES/g'                              Doxyfile
sed -i $extraArgument 's/GENERATE_TREEVIEW      = NO/GENERATE_TREEVIEW       = YES/g'                              Doxyfile
sed -i $extraArgument 's/FORMULA_FONTSIZE       = 10/FORMULA_FONTSIZE        = 14/g'                               Doxyfile
sed -i $extraArgument 's/DOT_FONTNAME           = Helvetica/DOT_FONTNAME     = Avenir/g'                           Doxyfile
sed -i $extraArgument 's/DOT_FONTSIZE           = 10/DOT_FONTSIZE            = 16/g'                               Doxyfile
sed -i $extraArgument 's/TEMPLATE_RELATIONS     = NO/TEMPLATE_RELATIONS      = YES/g'                              Doxyfile
sed -i $extraArgument 's/GENERATE_LATEX         = YES/GENERATE_LATEX         = NO/g'                               Doxyfile
sed -i $extraArgument 's/HAVE_DOT               = NO/HAVE_DOT                = YES/g'                              Doxyfile
sed -i $extraArgument 's/UML_LOOK               = NO/UML_LOOK                = YES/g'                              Doxyfile
sed -i $extraArgument 's/EXCLUDE                =/EXCLUDE                    = README.md .git/g'                   Doxyfile
sed -i $extraArgument 's/QUIET                  = NO/QUIET                   = YES/g'                              Doxyfile
sed -i $extraArgument 's/HIDE_FRIEND_COMPOUNDS  = NO/HIDE_FRIEND_COMPOUNDS   = YES/g'                              Doxyfile
sed -i $extraArgument 's/HTML_EXTRA_STYLESHEET  =/HTML_EXTRA_STYLESHEET      = mylayout.css/g'                     Doxyfile
sed -i $extraArgument 's/PREDEFINED             =/PREDEFINED                 = DOXYGEN_SHOULD_SKIP_THIS/g'         Doxyfile

# painfully removing the individual patterns
sed -i $extraArgument  '/*.hpp \\/d'      Doxyfile
sed -i $extraArgument  '/*.java \\/d'     Doxyfile
sed -i $extraArgument  '/*.ii \\/d'       Doxyfile
sed -i $extraArgument  '/*.ixx \\/d'      Doxyfile
sed -i $extraArgument  '/*.ipp \\/d'      Doxyfile
sed -i $extraArgument  '/*.i++ \\/d'      Doxyfile
sed -i $extraArgument  '/*.inl \\/d'      Doxyfile
sed -i $extraArgument  '/*.cs \\/d'       Doxyfile
sed -i $extraArgument  '/*.d \\/d'        Doxyfile
sed -i $extraArgument  '/*.m \\/d'        Doxyfile
sed -i $extraArgument  '/*.doc \\/d'      Doxyfile
sed -i $extraArgument  '/*.txt \\/d'      Doxyfile
sed -i $extraArgument  '/*.f \\/d'        Doxyfile
sed -i $extraArgument  '/*.for \\/d'      Doxyfile
sed -i $extraArgument  '/*.vhd \\/d'      Doxyfile
sed -i $extraArgument  '/*.ucf \\/d'      Doxyfile
sed -i $extraArgument  '/*.md \\/d'       Doxyfile
sed -i $extraArgument  '/*.mm \\/d'       Doxyfile
sed -i $extraArgument  '/*.dox \\/d'      Doxyfile
sed -i $extraArgument  '/*.f90 \\/d'      Doxyfile
sed -i $extraArgument  '/*.f95 \\/d'      Doxyfile
sed -i $extraArgument  '/*.f03 \\/d'      Doxyfile
sed -i $extraArgument  '/*.f08 \\/d'      Doxyfile
sed -i $extraArgument  '/*.markdown \\/d' Doxyfile
sed -i $extraArgument  '/*.tcl \\/d'      Doxyfile
sed -i $extraArgument  '/*.vhdl \\/d'     Doxyfile
sed -i $extraArgument  '/*.qsf \\/d'      Doxyfile
sed -i $extraArgument  '/*.php \\/d'      Doxyfile
sed -i $extraArgument  '/*.php4 \\/d'     Doxyfile
sed -i $extraArgument  '/*.php5 \\/d'     Doxyfile
sed -i $extraArgument  '/*.phtml \\/d'    Doxyfile
sed -i $extraArgument  '/*.idl \\/d'      Doxyfile
sed -i $extraArgument  '/*.ddl \\/d'      Doxyfile
sed -i $extraArgument  '/*.odl \\/d'      Doxyfile

rm -f Doxyfilebackup


