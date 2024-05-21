#!/bin/bash

# Create the database
python3 create_database.py

# Retrieve data
python3 retrieve_data.py > retrieved_data.txt

# Compile and run the C++ processing script
g++ -o process_data process_data.cpp -lsqlite3
./process_data

# Train the model
python3 train_model.py
