SCRIPT_DIR=`dirname $0`
pushd $SCRIPT_DIR/build
ninja -j4 && test/runtests
popd
