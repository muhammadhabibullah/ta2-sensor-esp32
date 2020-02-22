
// Write to the SD card (DON'T MODIFY THIS FUNCTION)
void writeFile(fs::FS &fs, const char * path, const char * message) {
    
    Serial.printf("Writing file: %s\n", path);
  
    File file = fs.open(path, FILE_WRITE);
    if(!file) {
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)) {
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
  
}

// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
void appendFile(fs::FS &fs, const char * path, const char * message) {
    
    Serial.printf("Appending to file: %s\n", path);
  
    File file = fs.open(path, FILE_APPEND);
    if(!file) {
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)) {
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}


// Create data to the SD card with spesific file path input
void createFile(const char * path) {
    
    // If the data file doesn't exist
    // Create a file on the SD card and write the data labels
    File file = SD.open(path);
    if(!file) {
        Serial.print(path);
        Serial.println(" file doesn't exist");
        Serial.println("Creating file...");
    }
    else {
        Serial.print(path);
        Serial.println(" file already exists");  
    }
    file.close();
}

void renameFile(const char * path, const char * newPath) {
	bool renamed = SD.rename(path, newPath);
	if (!renamed) {
		Serial.print(path);
		Serial.println(" file failed to renamed");
	} else {
		Serial.print(path);
		Serial.print(" file renamed to ");
		Serial.println(newPath);
	}
}

void removeFile(const char * path) {
    bool removed = SD.remove(path);
    if (!removed) {
        Serial.print(path);
		Serial.println(" file failed to removed");
    } else  {
        Serial.print(path);
		Serial.println(" file removed");
    }
}
