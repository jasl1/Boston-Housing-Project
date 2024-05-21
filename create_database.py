import sqlite3
from sklearn.datasets import load_boston
import pandas as pd

# Load Boston Housing dataset
boston = load_boston()
data = pd.DataFrame(boston.data, columns=boston.feature_names)
data['PRICE'] = boston.target

# Connect to SQLite database
conn = sqlite3.connect('boston_housing.db')
c = conn.cursor()

# Create table
c.execute('''
    CREATE TABLE IF NOT EXISTS housing_data (
        ID INTEGER PRIMARY KEY,
        CRIM REAL,
        ZN REAL,
        INDUS REAL,
        CHAS INTEGER,
        NOX REAL,
        RM REAL,
        AGE REAL,
        DIS REAL,
        RAD INTEGER,
        TAX REAL,
        PTRATIO REAL,
        B REAL,
        LSTAT REAL,
        PRICE REAL
    )
''')

# Insert data into the table
data.to_sql('housing_data', conn, if_exists='replace', index_label='ID')

# Close connection
conn.close()
