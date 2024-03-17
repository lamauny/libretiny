mkdir -p site/
boardgen ltci
python3 docs/scripts/write_boards.py
python3 docs/scripts/write_apis.py
python3 docs/scripts/prepare_doxygen.py
python3 docs/scripts/build_json.py
cp *.json site/
