#!/bin/bash

MAXN=5000
MAXM=5000
NEXEC=50

#Questo script esegue TemplateSeq_main per matrici di dimensioni crescenti (fino a MAXN, MAXM)
#e prende come valore dei tempi la media su NEXEC esecuzioni. 
#Salva le dimensioni delle matrici, media, varianza e stdev su un file esterno

#printf "MAXM = $MAXM, MAXN = $MAXN\n"
for((m=10;m<MAXM;m+=10)) do 
	for((n=10;n<MAXN;n+=10)) do
		printf "m = $m, n = $n \t" >> tempiSeq_${MAXM}x${MAXN}_avg_sampleSize${NEXEC}.txt;
		#I take the average over NEXEC elements as the time value for the given m and n 
		for((k=0;k<$NEXEC;k++)) do
			../Sequential/TemplateSeq_main $m $n 123 10 n;
		done > SeqHolders/tempiSeq_holder_${m}x${n}_${NEXEC}iter.txt;
		#Apparently, I have to store intermediate results into some support files
		awk '{sum+=$4;sumsq+=$4*$4;}
			{avg=sum/NR;} 
			END{var=sumsq/NR-(avg*avg);
				stdev=sqrt(var);
				print "avg =",avg,$5,"\t var =",var,$5,"\t stdev =",stdev; 
				}' SeqHolders/tempiSeq_holder_${m}x${n}_${NEXEC}iter.txt >> tempiSeq_${MAXM}x${MAXN}_avg_sampleSize${NEXEC}.txt
	done
done
# instead of >>, one can also use | tee -a file.txt