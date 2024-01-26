This is largely based off of <a href="https://numpy.org/doc/stable/user/c-info.ufunc-tutorial.html">this article.</a> <br><br>

To build it and run the tests:
```
python3.12 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
python setup.py build_ext --inplace
pip install .
pytest
```