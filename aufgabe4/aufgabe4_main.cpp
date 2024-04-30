/*
Mobarak Almoustafa
Finn Thierolf
06.12.23
aufgabe4
*/

#include "BLAST_Neighborhood.hpp"
#include <omp.h>

int main(int argc, const char* argv[])
{
    // Überprüfen, ob das Programm mit der richtigen Anzahl an Befehlszeilenargumenten aufgerufen wird
    if (argc == 6)
    {
        // Eine Instanz der Klasse BLAST_Neighborhood erstellen
        BLAST_Neighborhood neighborhood;
        
        // Eine Instanz der Klasse ScoreMatrix erstellen
        ScoreMatrix matrix;
        
        // Die Score-Matrix aus der Datei laden, die durch das zweite Befehlszeilenargument angegeben ist
        matrix.load(argv[2]);
        
        // Die aktuelle Zeit abrufen
        double start = omp_get_wtime();
        
        // Die Neighborhood unter Verwendung der angegebenen Sequenz, Score-Matrix, Wortgröße, Schwellenwert und Anzahl der Threads generieren
        std::vector<NHResult> results = neighborhood.generateNeighborhood(argv[1], matrix, std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]));
        
        // Die aktuelle Zeit abrufen
        double end = omp_get_wtime();
        
        // Über jedes NHResult-Element in dem Ergebnisvektor iterieren
        for (NHResult element : results)
        {
            // Die Infix-Sequenz ausgeben
            std::cout << element.infix << ": ";
            
            // Über jedes Nachbarpaar in dem Nachbarvektor iterieren
            for (std::pair tuple : element.neighbors)
            {
                // Das Nachbarpaar ausgeben
                std::cout << "(" << tuple.first << ", " << tuple.second << ") ";
            }
            
            // Eine neue Zeile ausgeben
            std::cout << std::endl;
        }
        
        // Die Ausführungszeit in Sekunden ausgeben
        std::cout << end - start << "s" << std::endl;
    }
    
    // Wenn das Programm nicht mit der richtigen Anzahl an Befehlszeilenargumenten aufgerufen wird
    else
    {
        // Eine logic_error mit einer Fehlermeldung werfen
        throw std::logic_error("Eingabe: ./aufgabe4_main sequenz score_matrix wortgröße schwellenwert threads");
    }
    
}