/*Ejercicio 4.7.6.3. Analizar traba en JSON
El objetivo de este ejercicio es implementar un analizador de tramas json en el microcontrolador que valide la integridad, el tipado y la estructura de los datos recibidos por puerto serie.

El sistema debe procesar objetos json que contengan las siguientes claves obligatorias:

Clave	Tipo de dato	Descripción
ID	string	Identificador único del dispositivo
Temperatura	int o float	Valor numérico ambiental
Humedad	int o float	Valor numérico de humedad relativa
Distancia	int o float	Valor numérico de proximidad

El firmware del microcontrolador debe seguir estrictamente estas directrices de procesamiento:

Independencia del orden: El programa debe localizar las claves sin importar la posición en la que aparezcan dentro del objeto json.
Validación de integridad:
Si el mensaje contiene todas las claves requeridas, se deben extraer los valores e imprimirlos por el puerto serie.
Si falta al menos una clave obligatoria, el sistema debe imprimir un mensaje de error específico por serial.
Validación de tipo:
Se debe verificar que cada valor corresponda al tipo de dato especificado (string para ID, numérico para los demás)
Si se detecta un tipo de dato incorrecto, el mensaje debe ser ignorado por completo.
Manejo de claves excedentes:
Si el objeto contiene claves adicionales a las solicitadas, estas deben ser ignoradas.

El programa debe procesar y mostrar únicamente las cuatro claves obligatorias.
Simulación: https://wokwi.com/projects/new/esp-idf-esp32
*/
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "cJSON.h"

static const char *TAG = "JSON_PARSER";

void procesar_trama_json(const char *json_raw) {
    // Intentar parsear el objeto JSON
    cJSON *root = cJSON_Parse(json_raw);
    if (root == NULL) {
        printf("Error: Formato JSON invalido.\n");
        return;
    }

    // 1. Obtener punteros a las claves (Independencia del orden)
    cJSON *id = cJSON_GetObjectItem(root, "ID");
    cJSON *temp = cJSON_GetObjectItem(root, "Temperatura");
    cJSON *hum = cJSON_GetObjectItem(root, "Humedad");
    cJSON *dist = cJSON_GetObjectItem(root, "Distancia");

    // 2. Validación de Integridad: ¿Existen todas las claves obligatorias?
    if (id == NULL || temp == NULL || hum == NULL || dist == NULL) {
        printf("Error: Faltan claves obligatorias en el JSON.\n");
        cJSON_Delete(root);
        return;
    }

    // 3. Validación de Tipo: ¿Los datos corresponden a lo especificado?
    // ID -> string, los demás -> numéricos
    if (!cJSON_IsString(id) || !cJSON_IsNumber(temp) || 
        !cJSON_IsNumber(hum) || !cJSON_IsNumber(dist)) {
        // Si el tipo es incorrecto, el mensaje se ignora por completo
        cJSON_Delete(root);
        return; 
    }

    // 4. Extracción y Salida (Manejo de claves excedentes es automático con cJSON_GetObjectItem)
    printf("--- Datos Recibidos ---\n");
    printf("ID: %s\n", id->valuestring);
    printf("Temperatura: %.2f\n", temp->valuedouble);
    printf("Humedad: %.2f\n", hum->valuedouble);
    printf("Distancia: %.2f\n", dist->valuedouble);
    printf("-----------------------\n");

    // Liberar memoria
    cJSON_Delete(root);
}

void app_main(void) {
    // Ejemplo de trama correcta
    const char *trama_valida = "{\"Temperatura\": 25.5, \"ID\": \"ESP32_01\", \"Distancia\": 10.2, \"Humedad\": 60, \"Extra\": 99}";
    
    // Ejemplo con error de tipo (Humedad como string)
    const char *trama_error_tipo = "{\"ID\": \"ESP32_01\", \"Temperatura\": 22.0, \"Humedad\": \"60\", \"Distancia\": 5.0}";

    printf("Probando trama valida:\n");
    procesar_trama_json(trama_valida);

    printf("\nProbando trama con error de tipo (debe ser ignorada):\n");
    procesar_trama_json(trama_error_tipo);
}
