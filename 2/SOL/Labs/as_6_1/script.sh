if [ $# -ne 1 ]; then                        # se il numero di arguments NOT EQUAL 1
    echo use: $(basename $0) nomedirectory   # stampo il comando d'uso (nomescript nomedirectory)
    exit -1
fi
dir=$1
if [ ! -d $dir ]; then                       # se $dir non è una directory
    echo "L'argomento $dir non e' una directory"   #stampo l'errore 
    exit 1;   
fi

bdir=$(basename $dir)
if [ -w $bdir.tar.gz ]; then                     # il file esiste ed e scrivibile
    echo -n "il file $bdir.tar.gz esiste gia', sovrascriverlo (S/N)?"
    read yn                                 # attendo un carattere da input utente
    if [ x$yn != x"S" ]; then               # se il valore dell'input non è S
          exit 0;                           # esco
    fi
    rm -f $bdir.tar.gz                      #altrimenti procedo a sovrascrivere
fi
echo "creo l'archivio con nome $bdir.tar.gz"

tar cf $bdir.tar $dir 2>> ./error.txt       # appende l’output sullo std-error nel file error.txt   
if [ $? -ne 0 ]; then                         # controlla che il comando sia andato a buon fine
    echo "Errore nella creazione dell'archivio"
    exit 1
fi
gzip $bdir.tar  2>> ./error.txt                  # appende l’output sullo std-error nel file error.txt
if [ $? -ne 0 ]; then                         # controlla che il comando sia andato a buon fine
    echo
    echo "Errore nella compressione dell'archivio"
    exit 1
fi

echo "archivio creato con successo, il contenuto dell’archivio e':"
tar tzvf $bdir.tar.gz   2>&1          # redirige lo std-error sullo std-output
exit 0