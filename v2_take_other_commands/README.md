editing orig file to spawn shell only upon receiving "SHELL" 
try another command -- TEST -- to output a string. 

Current issues:
- fgets string and command matches but does not enter 
- strcmp = 10 when cmd matches preset command 
- ctrl+D & enter need to be handled 
- change shutdown & replace system()