
// #include <Arduino.h>
// #include <WiFi.h>

// //----------------------------------------------
// // GLOBAL VARIABLES and CONSTANTS
// // your code here


// //----------------------------------------------
// // FUNCTIONS

// //----------------------------------------------
// // SETUP FUNCTION
// void setup(void) 
// {
//     // your code here
// }


// //----------------------------------------------
// // LOOP FUNCTION
// void loop(void) 
// {
//     // your code here
// }

// #define ESP32
// #define BOARD_HAS_PSRAM

#include <Arduino.h>
#include <ESP.h>
#include <esp_partition.h>
#include <esp_ota_ops.h>
#include <SPIFFS.h>

void printPartitionInfo() {
  Serial.println("\n========== PARTITION TABLE ==========");
  
  esp_partition_iterator_t pi = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);
  
  if (pi != NULL) {
    do {
      const esp_partition_t* p = esp_partition_get(pi);
      
      Serial.print("Partition: ");
      Serial.print(p->label);
      Serial.print(" | Type: ");
      
      // Print partition type
      switch(p->type) {
        case ESP_PARTITION_TYPE_APP:
          Serial.print("APP");
          break;
        case ESP_PARTITION_TYPE_DATA:
          Serial.print("DATA");
          break;
        default:
          Serial.print("OTHER");
      }
      
      Serial.print(" | SubType: ");
      
      // Print partition subtype
      if (p->type == ESP_PARTITION_TYPE_APP) {
        switch(p->subtype) {
          case ESP_PARTITION_SUBTYPE_APP_OTA_0:
            Serial.print("OTA_0");
            break;
          case ESP_PARTITION_SUBTYPE_APP_OTA_1:
            Serial.print("OTA_1");
            break;
          case ESP_PARTITION_SUBTYPE_APP_FACTORY:
            Serial.print("FACTORY");
            break;
          default:
            Serial.print(p->subtype);
        }
      } else if (p->type == ESP_PARTITION_TYPE_DATA) {
        switch(p->subtype) {
          case ESP_PARTITION_SUBTYPE_DATA_OTA:
            Serial.print("OTA");
            break;
          case ESP_PARTITION_SUBTYPE_DATA_NVS:
            Serial.print("NVS");
            break;
          case ESP_PARTITION_SUBTYPE_DATA_SPIFFS:
            Serial.print("SPIFFS");
            break;
          default:
            Serial.print(p->subtype);
        }
      } else {
        Serial.print(p->subtype);
      }
      
      Serial.print(" | Offset: 0x");
      Serial.print(p->address, HEX);
      Serial.print(" | Size: ");
      Serial.print(p->size);
      Serial.print(" bytes (");
      Serial.print(p->size / 1024);
      Serial.println(" KB)");
      
    } while ((pi = esp_partition_next(pi)) != NULL);
    
    esp_partition_iterator_release(pi);
  }
  
  Serial.println("=====================================\n");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n========== ESP32 MEMORY INFO ==========\n");

  // Flash Memory
  Serial.println("--- FLASH MEMORY ---");
  Serial.print("Flash chip size: ");
  Serial.print(ESP.getFlashChipSize());
  Serial.print(" bytes (");
  Serial.print(ESP.getFlashChipSize() / (1024 * 1024));
  Serial.println(" MB)");

  Serial.print("Flash chip speed: ");
  Serial.print(ESP.getFlashChipSpeed() / 1000000);
  Serial.println(" MHz");

  // Sketch size
  Serial.print("Sketch size: ");
  Serial.print(ESP.getSketchSize());
  Serial.print(" bytes (");
  Serial.print(ESP.getSketchSize() / 1024);
  Serial.println(" KB)");

  Serial.print("Free sketch space: ");
  Serial.print(ESP.getFreeSketchSpace());
  Serial.print(" bytes (");
  Serial.print(ESP.getFreeSketchSpace() / 1024);
  Serial.println(" KB)");

  // Heap (SRAM)
  Serial.println("\n--- HEAP (SRAM) ---");
  Serial.print("Heap total size: ");
  Serial.print(ESP.getHeapSize());
  Serial.println(" bytes");

  Serial.print("Heap free: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");

  Serial.print("Heap minimum free ever: ");
  Serial.print(ESP.getMinFreeHeap());
  Serial.println(" bytes");

  Serial.print("Maximum allocatable heap: ");
  Serial.print(ESP.getMaxAllocHeap());
  Serial.println(" bytes");

  // PSRAM (for WROVER variants or boards with external RAM)
#if defined(BOARD_HAS_PSRAM) || defined(ESP32)
  Serial.println("\n--- PSRAM ---");
  Serial.print("PSRAM total size: ");
  Serial.print(ESP.getPsramSize());
  Serial.println(" bytes");

  Serial.print("PSRAM free: ");
  Serial.print(ESP.getFreePsram());
  Serial.println(" bytes");
#endif

  // SPIFFS Information
  Serial.println("\n--- SPIFFS (SPI Flash File System) ---");
  if (SPIFFS.begin(true)) {
    Serial.println("SPIFFS mounted successfully");
    
    Serial.print("SPIFFS total size: ");
    Serial.print(SPIFFS.totalBytes());
    Serial.print(" bytes (");
    Serial.print(SPIFFS.totalBytes() / 1024);
    Serial.println(" KB)");
    
    Serial.print("SPIFFS used: ");
    Serial.print(SPIFFS.usedBytes());
    Serial.print(" bytes (");
    Serial.print(SPIFFS.usedBytes() / 1024);
    Serial.println(" KB)");
    
    Serial.print("SPIFFS free: ");
    Serial.print(SPIFFS.totalBytes() - SPIFFS.usedBytes());
    Serial.print(" bytes (");
    Serial.print((SPIFFS.totalBytes() - SPIFFS.usedBytes()) / 1024);
    Serial.println(" KB)");
  } else {
    Serial.println("SPIFFS mount failed!");
  }

  // Print all partitions
  printPartitionInfo();

  // Running partition info
  Serial.println("--- CURRENT RUNNING PARTITION ---");
  const esp_partition_t* running = esp_ota_get_running_partition();
  if (running != NULL) {
    Serial.print("Running from partition: ");
    Serial.println(running->label);
    Serial.print("Partition address: 0x");
    Serial.println(running->address, HEX);
    Serial.print("Partition size: ");
    Serial.print(running->size);
    Serial.print(" bytes (");
    Serial.print(running->size / 1024);
    Serial.println(" KB)");
  }

  Serial.println("\n=======================================\n");
}

void loop() {
  // Nothing needed here
}
