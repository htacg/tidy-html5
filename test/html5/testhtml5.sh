set -eu

noexe()
{
	echo "Unable to find/run exe ${TMPEXE}! *** FIX ME ***"
	echo "Set the name of the 'tidy' executable to use..."
	exit 1
}

noout()
{
	echo "Unable to creat ${TMPDIR}"
	exit 1
}

failed()
{
	echo "The test of ${f} FAILED!";
	TMPCNT3=$((${TMPCNT3} + 1));
}

TMPEXE="../../build/cmake/tidy"
[ -e ${TMPEXE} ] || noexe

TMPINP=temphtml5.cfg
TMPDIR=tempout

${TMPEXE} -h > /dev/null || noexe

if [ ! -e "${TMPDIR}" ]; then
	echo "Will create the folder ${TMPDIR} for output"
	read

	mkdir ${TMPDIR} || noout
fi

# This option would be nice, but at present it is FARRRR TOOOOO agressive,
# dropping <html>, <body>, etc...  because they are marked CM_OPT
# which causes WARNINGS when tidy is run on the tidied file!!!
# echo omit-optional-tags: yes >> ${TMPINP}

if [ ! -e "${TMPINP}" ]; then
	echo "Creating a CONFIG file ${TMPINP}"
	read

	cat <<EOF > ${TMPINP}
wrap: 99
tidy-mark: no
indent: yes
break-before-br: yes
indent-attributes: yes
vertical-space: yes
indent-spaces: 1
indent-cdata: no
wrap-asp: no
wrap-attributes: no
wrap-jste: no
wrap-php: no
wrap-script-literals: no
wrap-sections: no
tab-size: 4
show-info: no
EOF
fi

TMPCNT1=0
TMPCNT2=0
TMPCNT3=0

for f in *.org.html; do
	TMPCNT1=$((${TMPCNT1} + 1))
done

echo
echo "Will process ${TMPCNT1} files found..."
echo "All should exit with NO WARNINGS or ERRORS"
echo "*** CONTINUE? *** Only Ctlr+C aborts... all other keys continue..."

read

for f in *.org.html ; do
	TMPCNT2=$((${TMPCNT2} + 1))

	echo "${TMPCNT2} of ${TMPCNT1}"

	TMPOUT="${TMPDIR}/${f}"
	${TMPEXE} -config ${TMPINP} -o ${TMPOUT} ${f} || failed
done

echo
echo Done ${TMPCNT2} files. See tidied output in ${TMPDIR}
if [ "${TMPCNT3}" = 0 ]; then
	echo "With NO WARNINGS or ERRORS! This is a *** SUCCESS ***"
else
	echo "However have ${TMPCNT3} WARNINGS or ERRORS! This is a *** FAILURE ***"
fi
echo
