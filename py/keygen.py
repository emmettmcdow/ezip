from weatherbit.api import Api 
import random

def temp_map(temperature):
    temperature += 40
    if (temperature < 5):
        return "0"
    elif (temperature < 10):
        return "1"
    elif (temperature < 15):
        return "2"
    elif (temperature < 20):
        return "3"
    elif (temperature < 25):
        return "4"
    elif (temperature < 30):
        return "5"
    elif (temperature < 35):
        return "6"
    elif (temperature < 40):
        return "7"
    elif (temperature < 45):
        return "8"
    elif (temperature < 50):
        return "9"
    elif (temperature < 55):
        return "A"
    elif (temperature < 60):
        return "B"
    elif (temperature < 65):
        return "C"
    elif (temperature < 70):
        return "D"
    elif (temperature < 75):
        return "D"
    elif (temperature < 80):
        return "F"


api_key = "388a906c36084818ba4688a859cabee1"
api = Api(api_key)
key_values = ("0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F")
rtn_key = ""
for i in range(0, 32):
    lat = random.randrange(-90, 90)
    lon = random.randrange(-180, 80)
    forecast = api.get_forecast(lat=lat, lon=lon)
    temp = forecast.get_series(['temp'])[0]['temp']
    rtn_key += temp_map(temp)
print(rtn_key)
