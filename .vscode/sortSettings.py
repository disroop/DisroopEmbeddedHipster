
import json

with open('settings.json') as infile:
    json_data = json.load(infile)
    
a_json = json.dumps(json_data, sort_keys=True)

with open('a.json','w') as outfile:
    json.dump(a_json,outfile) 
