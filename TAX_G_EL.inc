***                                                                                                                                            Taxes on electricity production                                                                                                                                                                                                                                                
***                                                                                                                                            Negative values are interpreted as subsidies                                                                                                                                                                                                                                   
***                                                                                                                                            Oct-2018. Jon Gustav Kirkerud                                                                                                                                                                                                                                                  
PARAMETER TAX_G_EL(YYY,CCC,GGG) 'tax on electricity generation';                                                                                                                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                                                                                                                                                                              
*** Main input format: per country and per fuel                                                                                                                                                                                                                                                                                                                                                                               
TABLE TAX_G_EL_IN(YYY,CCC,FFF) 'tax on electricity generation'                                                                                                                                                                                                                                                                                                                                                                
                                                                                                                                               NUCLEAR                                                                                                                                                     NATGAS COAL  LIGNITE FUELOIL LIGHTOIL SHALE PEAT LNG   ELECTRIC WIND SUN  WOODCHIPS WOODPELLETS WOODWASTE MUNIWASTE
2015.DENMARK                                                                                                                                                                                                                                                                                               32.15  34.08         32.9    32.9                32.15                                                             
2015.FINLAND                                                                                                                                                                                                                                                                                                                                                                                                                  
2015.GERMANY                                                                                                                                                                                                                                                                                                                                                                                                                  
2015.NORWAY                                                                                                                                                                                                                                                                                                                                                                                                                   
2015.POLAND                                                                                                                                                                                                                                                                                                                                                                                                                   
2015.SWEDEN                                                                                                                                                                                                                                                                                                                                                                                                                   
2015.ESTONIA                                                                                                                                                                                                                                                                                                                                                                                                                  
2015.LATVIA                                                                                                                                                                                                                                                                                                                                                                                                                   
2015.LITHUANIA                                                                                                                                                                                                                                                                                                                                                                                                                
;                                                                                                                                                                                                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                                                                                                                                                                              
* Apply 2015 numbers to all years:                                                                                                                                                                                                                                                                                                                                                                                            
TAX_G_EL_IN(Y,C,FFF)$(YVALUE(Y) ne 2015) = TAX_G_EL_IN('2015',C,FFF);                                                                                                                                                                                                                                                                                                                                                         
                                                                                                                                                                                                                                                                                                                                                                                                                              
* Assign values onto TAX_G_EL                                                                                                                                                                                                                                                                                                                                                                                                 
TAX_G_EL(Y,C,IGE)$((SUM(IA$ICA(C,IA), GKFX(Y,IA,IGE)) > 0) OR SUM(IA$ICA(C,IA), AGKN(IA,IGE)))  = SUM(FFF$IGF(IGE,FFF), TAX_G_EL_IN(Y,C,FFF));                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                                                                                                                                                              
*** Secondary input: exceptions from the main input on technology level                                                                                                                                                                                                                                                                                                                                                       
                                                                                                                                                                                                                                                                                                                                                                                                                              
* For Danish fossil fuel plants, this tax only considers back pressure                                                                                                                                                                                                                                                                                                                                                        
TAX_G_EL(Y,'DENMARK',G)$((IGF(G,'NATGAS') OR IGF(G,'COAL') OR IGF(G,'FUELOIL') OR IGF(G,'LIGHTOIL') OR IGF(G,'LNG'))  AND NOT IGBPR(G) ) = 0;                                                                                                                                                                                                                                                                                 
                                                                                                                                                                                                                                                                                                                                                                                                                              
* For back pressure: use E-rule if that result in lower cost than V-rule. If not, set to zero.                                                                                                                                                                                                                                                                                                                                
TAX_G_EL(Y,'DENMARK',IGBPR)$(                                                                                                                  (IGF(IGBPR,'NATGAS') OR IGF(IGBPR,'COAL') OR IGF(IGBPR,'FUELOIL') OR IGF(IGBPR,'LIGHTOIL') OR IGF(IGBPR,'LNG'))                                                                                                                                                                
                                                                                                                                               AND(( 1 - (GDATA(IGBPR,'GDCB') * GDATA(IGBPR,'GDFE') / (1 + GDATA(IGBPR,'GDCB')) ) / 0.67) < (GDATA(IGBPR,'GDFE')/ ( 1 + GDATA(IGBPR,'GDCB'))/1.2)))  =                                                                                                                        
                                                                                                                                               TAX_G_EL(Y,'DENMARK',IGBPR) / 0.67;                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                                                              
TAX_G_EL(Y,'DENMARK',IGBPR)$(                                                                                                                  (IGF(IGBPR,'NATGAS') OR IGF(IGBPR,'COAL') OR IGF(IGBPR,'FUELOIL') OR IGF(IGBPR,'LIGHTOIL') OR IGF(IGBPR,'LNG'))                                                                                                                                                                
                                                                                                                                               AND (( 1 - (GDATA(IGBPR,'GDCB') * GDATA(IGBPR,'GDFE') / (1 + GDATA(IGBPR,'GDCB')) ) / 0.67) > (GDATA(IGBPR,'GDFE')/ ( 1 + GDATA(IGBPR,'GDCB'))/1.2)))  = 0;                                                                                                                    