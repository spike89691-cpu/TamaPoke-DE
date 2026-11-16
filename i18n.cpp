#include "i18n.h"
#include "dex.h"  // DEX_TBL, DEX_COUNT
#include "pet.h"        // MED_COUNT
#include "move_names.h"
#include <Preferences.h>
#include "nvsinfo.h"   // logKeyFailure(): the lang setting write was silent

Lang gLang = LANG_DEFAULT;
static_assert(LANG_COUNT == MOVE_NAME_LANG_COUNT, "move-name language order must match Lang");

// Tabla de cadenas [idioma][id]. Sin acentos ni enes: la fuente bitmap del
// firmware no los tiene (por eso el espanol ya iba "Esta", "bano", etc.).
static const char *const STRINGS[LANG_COUNT][STR_COUNT] = {
  // ---------------- ES ----------------
  {
    "Esta evolucionando!", "Nam nam!", "Le gusta!", "Tiene hambre!", "Necesita un bano!",
    "Esta agotado...", "Esta triste...", "Esta rellenito...", "Es SHINY!!", "Esta feliz",
    "GRACIAS! Hasta siempre", "Se ha escapado...", "Adios! Se despide...",
    "HUEVO", "Huevo legendario!?", "Huevo raro!", "Toca el huevo...", "Se mueve!", "Esta a punto!",
    "POKEDEX %u/%u",
    "%s%s Nv.%u",
    "Soltar a %s?", "SI", "NO",
    "%u GOLPES", "FUERZA +%u", "NUEVO RECORD!", "RECORD: %u", "APORREA RAPIDO!",
    "PUNTOS: %u", "Que felicidad!", "+felicidad",
    "AJUSTAR HORA", "HORA", "MIN", "desliza abajo: cancelar", "Idioma",
    "MEDALLA!", "GENIAL!", "RACHA %u DIAS!",
    "RACHA %u  rec %u", "VIN", "BAYA ???", "BAYA ROJA", "BAYA AZUL", "BAYA VERDE",
    "%s   EDAD %lud", "toca el nombre: renombrar",
    "COMBATE", "FUE", "DEF", "VEL", "PES", "ENTRENAR FUERZA",
    "MEDALLAS %d/%d", "toca: volver",
    "NOMBRE:", "toca para volver",
    "COM", "FEL", "ENE", "LIM",
    "REC %u",
    "PROGRESO", "Nv.%u", "%u min para Nv.%u", "EVOLUCION", "Forma final",
    "Listo para evolucionar!", "Sube todo a 40 para evolucionar",
    "Evoluciona en %u niv.", "Descuidos: %u",
    "SON ON", "SON OFF",
    "EVOLUCIONAR", "%s quiere decirte algo...", "%s se siente abandonado...",
    "Evolucionar?", "Mantener forma", "Despedirse?", "Despedirse", "Quedaros juntos",
    "Elige tu inicial",
    "Sin sprites", "Cargalos en la SD",
    "PS", "IV %u",
    "MENU", "AJUSTES", "CERRAR", "EQUIPO %u/6", "EQUIPO", "- vacio -", "%s se une al equipo!", "Equipo lleno: elige a quien sustituir", "Dejarlo ir",
    "STATS", "ENTRENAR", "FUERZA", "VELOCIDAD", "DEFENSA", "Sube sola si esta a gusto",
    "MOVIMIENTOS", "- vacio -", "Elige movimiento", "Toca para cambiar", "POT %u", "ESTADO",
    "%s quiere aprender", "No aprender",
    "%s usa %s", "Es muy eficaz!", "No es muy eficaz...", "No le afecta...",
    "%s ha fallado!", "Golpe critico!", "%s se debilita!", "Se ha herido!",
    "%s: %s", "PARALISIS", "QUEMADURA", "VENENO", "DORMIDO", "CONGELADO", "CONFUSION",
    "Has ganado!", "Has perdido...",
    "%s saca a %s", "Adelante, %s!", "GIMNASIOS", "MEDALLAS %u/8", "ENTRENADOR", "VELOCIDAD +%u", "toca: cambiar avatar", "%u en total", "NORMAL", "DIFICIL",
 "ELEGIDOS %u/%u", "LUCHAR", "BLOQUEADO", "POKEMON", "%s derrotado!", "MEDALLA NUEVA!", "VOL %u", "CAJA %u/%u", "cambiar con %s: elige hueco", "CAJA", "TRAER", "solo con un huevo", "COMBATE LAN", "CREAR", "UNIRSE", "buscando...", "listo!", "version distinta", "crear o unirse", "rival: %u mons", "el rival se fue", "esperando al rival...", "OTRA VEZ", "HUIR", "de que region viene el huevo", "%s +%u", "ya no puede entrenar mas", "ELIGE TU REGION", "RETIRAR", "Retirarla ya?", "la siguiente evoluciona un dia mas tarde", "evoluciona un dia mas tarde",   "FALTA PACK", "SOLTAR", "se va para siempre", "AL EQUIPO", "no se unira a tu equipo",
    "MOCHILA", "MOCHILA VACIA", "EXPLORAR", "Aparece un %s salvaje!", "%s ha huido!",
    "Has escapado!", "No has podido escapar!", "Lanzas una %s", "%s capturado!", "Se ha soltado!",
    "Usas %s", "No ha hecho nada", "Encuentras %s!", "CRIAR A ESTE", "CRIANDO",
    "SALIR", "Salir de la lucha?",
    "vencido: %u vez", "vencido: %u veces", "perdiste: %u vez", "perdiste: %u veces",
    "TIENDA POKE", "1 paso = $1", "tus pasos de toda la vida: %lu", "Wallet: $%lu", "Comprar %s?", "COSTE: $%lu", },
  // ---------------- EN ----------------
  {
    "Evolving!", "Yum yum!", "It likes it!", "It's hungry!", "Needs a bath!",
    "Worn out...", "Feeling sad...", "A bit chubby...", "It's SHINY!!", "It's happy",
    "THANKS! Farewell", "It ran away...", "Bye! Waving goodbye...",
    "EGG", "Legendary egg!?", "Rare egg!", "Tap the egg...", "It moves!", "Almost there!",
    "POKEDEX %u/%u",
    "%s%s Lv.%u",
    "Release %s?", "YES", "NO",
    "%u HITS", "STR +%u", "NEW RECORD!", "BEST: %u", "HIT FAST!",
    "SCORE: %u", "So much fun!", "+happiness",
    "SET TIME", "HOUR", "MIN", "swipe down: cancel", "Lang",
    "MEDAL!", "AWESOME!", "%u DAY STREAK!",
    "STREAK %u  best %u", "BOND", "BERRY ???", "RED BERRY", "BLUE BERRY", "GREEN BERRY",
    "%s   AGE %lud", "tap name: rename",
    "BATTLE", "ATK", "DEF", "SPD", "WGT", "TRAIN STRENGTH",
    "MEDALS %d/%d", "tap: back",
    "NAME:", "tap to go back",
    "FOOD", "JOY", "ENE", "HYG",
    "BEST %u",
    "PROGRESS", "Lv.%u", "%u min to Lv.%u", "EVOLUTION", "Final form",
    "Ready to evolve!", "All needs >=40 to evolve",
    "Evolves in %u lv.", "Slip-ups: %u",
    "SND ON", "SND OFF",
    "EVOLVE!", "%s wants to tell you...", "%s feels abandoned...",
    "Evolve?", "Keep form", "Say goodbye?", "Goodbye", "Stay together",
    "Choose your starter",
    "No sprites", "Load them onto the SD",
    "HP", "IV %u",
    "MENU", "SETTINGS", "CLOSE", "PARTY %u/6", "PARTY", "- empty -", "%s joined the party!", "Party full: pick who to replace", "Let it go",
    "STATS", "TRAINING", "STRENGTH", "SPEED", "DEFENCE", "Grows on its own when happy",
    "MOVES", "- empty -", "Choose a move", "Tap a slot to change", "PWR %u", "STATUS",
    "%s wants to learn", "Do not learn",
    "%s used %s", "Super effective!", "Not very effective...", "It had no effect...",
    "%s missed!", "Critical hit!", "%s fainted!", "It hurt itself!",
    "%s: %s", "PARALYSED", "BURNED", "POISONED", "ASLEEP", "FROZEN", "CONFUSED",
    "You win!", "You lost...",
    "%s sends out %s", "Go, %s!", "GYMS", "BADGES %u/8", "TRAINER",
 "SPEED +%u", "tap: change avatar", "%u earned in all", "EASY", "HARD", "CHOSEN %u/%u", "FIGHT", "LOCKED", "POKEMON", "%s defeated!", "NEW BADGE!", "VOL %u", "BOX %u/%u", "swap with %s: pick a slot", "BOX", "BRING BACK", "only while an egg waits", "LAN BATTLE", "HOST", "JOIN", "searching...", "ready!", "different version", "host or join", "rival: %u mons", "the rival left", "waiting for the rival...", "AGAIN", "RUN", "where this egg comes from", "%s +%u", "trained as far as it can go", "CHOOSE A REGION", "RETIRE", "Retire it early?", "the next one evolves a day later", "evolves a day later",
   "NEEDS PACK", "RELEASE", "gone for good", "TO PARTY", "it will not join your party",
    "BAG", "BAG EMPTY", "EXPLORE", "A wild %s appeared!", "%s fled!",
    "You got away!", "You could not get away!", "You threw a %s", "%s was caught!", "It broke free!",
    "Used %s", "It had no effect", "Found %s!", "RAISE THIS ONE", "RAISING",
    "QUIT", "Leave the battle?",
    "defeated: %u time", "defeated: %u times", "lost to: %u time", "lost to: %u times",
    "POKE MART", "1 pedometer step = $1", "your lifetime step count: %lu", "Wallet: $%lu", "Buy %s?", "COST: $%lu", },
  // ---------------- FR ----------------
  {
    "Il evolue!", "Miam miam!", "Il aime ca!", "Il a faim!", "Besoin d'un bain!",
    "Epuise...", "Triste...", "Un peu rond...", "C'est SHINY!!", "Il est content",
    "MERCI! Adieu", "Il s'est enfui...", "Au revoir!",
    "OEUF", "Oeuf legendaire!?", "Oeuf rare!", "Touche l'oeuf...", "Il bouge!", "Presque la!",
    "POKEDEX %u/%u",
    "%s%s Niv.%u",
    "Relacher %s?", "OUI", "NON",
    "%u COUPS", "FORCE +%u", "NOUVEAU RECORD!", "RECORD: %u", "FRAPPE VITE!",
    "SCORE: %u", "Trop bien!", "+bonheur",
    "REGLER L'HEURE", "HEURE", "MIN", "glisse bas: annuler", "Langue",
    "MEDAILLE!", "SUPER!", "SERIE %u JOURS!",
    "SERIE %u  rec %u", "LIEN", "BAIE ???", "BAIE ROUGE", "BAIE BLEUE", "BAIE VERTE",
    "%s   AGE %lud", "touche le nom: renommer",
    "COMBAT", "ATQ", "DEF", "VIT", "PDS", "ENTRAINER FORCE",
    "MEDAILLES %d/%d", "touche: retour",
    "NOM:", "touche pour revenir",
    "NOUR", "JOIE", "ENE", "HYG",
    "REC %u",
    "PROGRES", "Niv.%u", "%u min pour Niv.%u", "EVOLUTION", "Forme finale",
    "Pret a evoluer!", "Tout a 40 pour evoluer",
    "Evolue dans %u niv.", "Negligences: %u",
    "SON ON", "SON OFF",
    "EVOLUER", "%s veut te parler...", "%s se sent abandonne...",
    "Evoluer?", "Garder forme", "Dire adieu?", "Adieu", "Rester ensemble",
    "Choisis ton starter",
    "Pas de sprites", "Charge-les sur la SD",
    "PV", "IV %u",
    "MENU", "REGLAGES", "FERMER", "EQUIPE %u/6", "EQUIPE", "- vide -", "%s rejoint l'equipe!", "Equipe pleine: qui remplacer?", "Le laisser partir",
    "STATS", "ENTRAINEMENT", "FORCE", "VITESSE", "DEFENSE", "Monte seule s'il est heureux",
    "CAPACITES", "- vide -", "Choisis une capacite", "Touche pour changer", "PUI %u", "STATUT",
    "%s veut apprendre", "Ne pas apprendre",
    "%s utilise %s", "Tres efficace!", "Peu efficace...", "Aucun effet...",
    "%s a rate!", "Coup critique!", "%s est K.O.!", "Il se blesse!",
    "%s: %s", "PARALYSIE", "BRULURE", "POISON", "ENDORMI", "GELE", "CONFUSION",
    "Gagne!", "Perdu...",
    "%s envoie %s", "Vas-y, %s!", "ARENES", "BADGES %u/8", "DRESSEUR", "VITESSE +%u", "touche: changer d'avatar", "%u au total", "NORMAL", "DIFFICILE", "CHOISIS %u/%u", "COMBATTRE", "VERROUILLE", "POKEMON", "%s vaincu!", "NOUVEAU BADGE!", "VOL %u", "BOITE %u/%u", "echanger avec %s: choisis", "BOITE", "RAMENER", "seulement avec un oeuf", "COMBAT LAN", "CREER", "REJOINDRE", "recherche...", "pret!", "version differente", "creer ou rejoindre", "rival: %u mons", "le rival est parti", "en attente du rival...", "ENCORE", "FUIR", "d ou vient cet oeuf", "%s +%u", "ne peut plus progresser", "CHOISIS TA REGION", "RETIRER", "Retirer maintenant?", "le suivant evolue un jour plus tard", "evolue un jour plus tard",
   "PACK REQUIS", "RELACHER", "parti pour de bon", "A L EQUIPE", "ne rejoindra pas l equipe",
    "SAC", "SAC VIDE", "EXPLORER", "Un %s sauvage apparait!", "%s a fui!",
    "Tu as pris la fuite!", "Impossible de fuir!", "Tu lances une %s", "%s est capture!", "Il s est libere!",
    "Tu utilises %s", "Aucun effet", "Tu trouves %s!", "ELEVER CELUI-CI", "EN ELEVAGE",
    "QUITTER", "Quitter le combat?",
    "vaincu: %u fois", "vaincu: %u fois", "perdu contre: %u fois", "perdu contre: %u fois",
    "POKE MART", "1 pas = $1", "tes pas de toute la vie: %lu", "Wallet: $%lu", "Acheter %s?", "COUT: $%lu", },
  // ---------------- DE ----------------
  {
    "Entwickelt sich!", "Mampf mampf!", "Gefaellt ihm!", "Hat Hunger!", "Braucht ein Bad!",
    "Erschoepft...", "Traurig...", "Etwas rundlich...", "Es ist SHINY!!", "Es ist froh",
    "DANKE! Lebwohl", "Es ist weg...", "Tschuess! Winkt",
    "EI", "Legendaeres Ei!?", "Seltenes Ei!", "Beruehre das Ei...", "Es bewegt sich!", "Fast soweit!",
    "POKEDEX %u/%u",
    "%s%s Lv.%u",
    "%s freilassen?", "JA", "NEIN",
    "%u TREFFER", "KRAFT +%u", "NEUER REKORD!", "REKORD: %u", "SCHNELL HAUEN!",
    "PUNKTE: %u", "Wie schoen!", "+Freude",
    "ZEIT STELLEN", "STD", "MIN", "runter wischen: abbruch", "Sprache",
    "MEDAILLE!", "TOLL!", "%u TAGE SERIE!",
    "SERIE %u  rek %u", "BND", "BEERE ???", "ROTE BEERE", "BLAUE BEERE", "GRUENE BEERE",
    "%s   ALTER %lud", "Name tippen: umbenennen",
    "KAMPF", "ANG", "VER", "INI", "GEW", "KRAFT TRAINIEREN",
    "MEDAILLEN %d/%d", "tippen: zurueck",
    "NAME:", "tippen zum zurueck",
    "ESS", "FRO", "ENE", "HYG",
    "REK %u",
    "FORTSCHRITT", "Lv.%u", "%u min bis Lv.%u", "ENTWICKLUNG", "Endform",
    "Bereit zur Entwicklung!", "Alles >=40 zur Entwicklung",
    "Entwickelt in %u Lv.", "Patzer: %u",
    "TON AN", "TON AUS",
    "ENTWICKELN", "%s will dir etwas sagen...", "%s fuehlt sich verlassen...",
    "Entwickeln?", "Form behalten", "Abschied?", "Lebwohl", "Zusammen bleiben",
    "Waehle dein Starter",
    "Keine Sprites", "Auf die SD laden",
    "KP", "IV %u",
    "MENU", "EINSTELLUNGEN", "SCHLIESSEN", "TEAM %u/6", "TEAM", "- leer -", "%s kommt ins Team!", "Team voll: wen ersetzen?", "Ziehen lassen",
    "WERTE", "TRAINING", "STAERKE", "TEMPO", "ABWEHR", "Steigt von selbst bei guter Laune",
    "ATTACKEN", "- leer -", "Attacke waehlen", "Tippen zum Aendern", "STK %u", "STATUS",
    "%s will lernen", "Nicht lernen",
    "%s setzt %s ein", "Sehr effektiv!", "Nicht sehr effektiv...", "Keine Wirkung...",
    "%s hat verfehlt!", "Volltreffer!", "%s wurde besiegt!", "Es verletzt sich!",
    "%s: %s", "PARALYSE", "VERBRANNT", "VERGIFTET", "SCHLAEFT", "GEFROREN", "VERWIRRT",
    "Gewonnen!", "Verloren...",
    "%s schickt %s", "Los, %s!", "ARENEN", "ORDEN %u/8", "TRAINER", "TEMPO +%u", "tippen: Avatar wechseln", "%u insgesamt", "NORMAL", "SCHWER", "GEWAEHLT %u/%u", "KAEMPFEN", "GESPERRT", "POKEMON", "%s besiegt!", "NEUER ORDEN!", "LAUT %u", "BOX %u/%u", "mit %s tauschen: waehle", "BOX", "ZURUECK", "nur mit einem Ei", "LAN KAMPF", "HOSTEN", "BEITRETEN", "suche...", "bereit!", "andere Version", "hosten oder beitreten", "Gegner: %u", "der Gegner ist weg", "warte auf den Gegner...", "NOCHMAL", "FLUCHT", "woher dieses Ei kommt", "%s +%u", "kann nicht weiter trainieren", "WAEHLE DEINE REGION", "VERABSCHIEDEN", "Jetzt verabschieden?", "das naechste entwickelt sich einen Tag spaeter", "entwickelt sich einen Tag spaeter",
   "PACK FEHLT", "FREILASSEN", "fuer immer weg", "INS TEAM", "kommt nicht ins team",
    "BEUTEL", "BEUTEL LEER", "ERKUNDEN", "Ein wildes %s erscheint!", "%s ist geflohen!",
    "Du bist entkommen!", "Flucht gescheitert!", "Du wirfst einen %s", "%s gefangen!", "Es ist entkommen!",
    "%s benutzt", "Keine Wirkung", "%s gefunden!", "DIESES AUFZIEHEN", "WIRD AUFGEZOGEN",
    "VERLASSEN", "Kampf verlassen?",
    "besiegt: %u Mal", "besiegt: %u Mal", "verloren gegen: %u Mal", "verloren gegen: %u Mal",
    "POKE MART", "1 Schritt = $1", "deine schritte insgesamt: %lu", "Wallet: $%lu", "%s kaufen?", "KOSTEN: $%lu", },
  // ---------------- IT ----------------
  {
    "Si evolve!", "Gnam gnam!", "Gli piace!", "Ha fame!", "Vuole un bagno!",
    "Esausto...", "Triste...", "Un po' cicciotto...", "E' SHINY!!", "E' felice",
    "GRAZIE! Addio", "E' scappato...", "Ciao! Saluta",
    "UOVO", "Uovo leggendario!?", "Uovo raro!", "Tocca l'uovo...", "Si muove!", "Ci siamo quasi!",
    "POKEDEX %u/%u",
    "%s%s Lv.%u",
    "Liberare %s?", "SI", "NO",
    "%u COLPI", "FORZA +%u", "NUOVO RECORD!", "RECORD: %u", "COLPISCI VELOCE!",
    "PUNTI: %u", "Che gioia!", "+felicita",
    "IMPOSTA ORA", "ORA", "MIN", "scorri giu: annulla", "Lingua",
    "MEDAGLIA!", "GRANDE!", "SERIE %u GIORNI!",
    "SERIE %u  rec %u", "LEG", "BACCA ???", "BACCA ROSSA", "BACCA BLU", "BACCA VERDE",
    "%s   ETA %lud", "tocca il nome: rinomina",
    "LOTTA", "ATT", "DIF", "VEL", "PES", "ALLENA FORZA",
    "MEDAGLIE %d/%d", "tocca: indietro",
    "NOME:", "tocca per tornare",
    "CIB", "GIO", "ENE", "IGI",
    "REC %u",
    "PROGRESSI", "Lv.%u", "%u min per Lv.%u", "EVOLUZIONE", "Forma finale",
    "Pronto a evolvere!", "Tutto a 40 per evolvere",
    "Evolve tra %u liv.", "Disattenzioni: %u",
    "AUD ON", "AUD OFF",
    "EVOLVI", "%s vuole dirti qualcosa...", "%s si sente abbandonato...",
    "Evolvere?", "Mantieni forma", "Salutare?", "Addio", "Restare insieme",
    "Scegli l'iniziale",
    "Senza sprite", "Caricali sulla SD",
    "PS", "IV %u",
    "MENU", "IMPOSTAZIONI", "CHIUDI", "SQUADRA %u/6", "SQUADRA", "- vuoto -", "%s entra in squadra!", "Squadra piena: chi sostituire?", "Lasciarlo andare",
    "STATS", "ALLENAMENTO", "FORZA", "VELOCITA", "DIFESA", "Sale da sola se sta bene",
    "MOSSE", "- vuoto -", "Scegli una mossa", "Tocca per cambiare", "POT %u", "STATO",
    "%s vuole imparare", "Non imparare",
    "%s usa %s", "Superefficace!", "Non molto efficace...", "Nessun effetto...",
    "%s ha mancato!", "Brutto colpo!", "%s e\' esausto!", "Si e ferito!",
    "%s: %s", "PARALISI", "SCOTTATURA", "VELENO", "ADDORMENTATO", "CONGELATO", "CONFUSIONE",
    "Hai vinto!", "Hai perso...",
    "%s manda %s", "Vai, %s!", "PALESTRE", "MEDAGLIE %u/8", "ALLENATORE", "VELOCITA +%u", "tocca: cambia avatar", "%u in totale", "NORMALE", "DIFFICILE", "SCELTI %u/%u", "LOTTA", "BLOCCATO", "POKEMON", "%s sconfitto!", "NUOVA MEDAGLIA!", "VOL %u", "BOX %u/%u", "scambia con %s: scegli", "BOX", "RIPORTA", "solo con un uovo", "LOTTA LAN", "CREA", "ENTRA", "ricerca...", "pronto!", "versione diversa", "crea o entra", "rivale: %u mons", "il rivale se n' e andato", "in attesa del rivale...", "ANCORA", "FUGGI", "da quale regione viene l uovo", "%s +%u", "non puo allenarsi oltre", "SCEGLI LA REGIONE", "RITIRARE", "Ritirarla adesso?", "il prossimo evolve un giorno dopo", "evolve un giorno dopo",
   "MANCA PACK", "LIBERA", "via per sempre", "AL GRUPPO", "non entrera nel gruppo",
    "ZAINO", "ZAINO VUOTO", "ESPLORA", "Appare un %s selvatico!", "%s e fuggito!",
    "Sei riuscito a fuggire!", "Non sei riuscito a fuggire!", "Lanci una %s", "%s catturato!", "Si e liberato!",
    "Usi %s", "Nessun effetto", "Trovi %s!", "ALLEVA QUESTO", "IN ALLEVAMENTO",
    "ESCI", "Uscire dalla lotta?",
    "battuto: %u volta", "battuto: %u volte", "perso contro: %u volta", "perso contro: %u volte",
    "POKE MART", "1 passo = $1", "i tuoi passi di sempre: %lu", "Wallet: $%lu", "Comprare %s?", "COSTO: $%lu", },
  // ---------------- PT ----------------
  {
    "Evoluindo!", "Nham nham!", "Ele gosta!", "Esta com fome!", "Precisa de banho!",
    "Exausto...", "Triste...", "Um pouco gordinho...", "E SHINY!!", "Esta feliz",
    "OBRIGADO! Adeus", "Fugiu...", "Tchau! Acena",
    "OVO", "Ovo lendario!?", "Ovo raro!", "Toque no ovo...", "Mexe-se!", "Quase la!",
    "POKEDEX %u/%u",
    "%s%s Niv.%u",
    "Soltar %s?", "SIM", "NAO",
    "%u GOLPES", "FORCA +%u", "NOVO RECORDE!", "RECORDE: %u", "BATA RAPIDO!",
    "PONTOS: %u", "Que alegria!", "+alegria",
    "AJUSTAR HORA", "HORA", "MIN", "deslize baixo: cancelar", "Idioma",
    "MEDALHA!", "OTIMO!", "%u DIAS SEGUIDOS!",
    "SEQ %u  rec %u", "LACO", "BAGA ???", "BAGA VERMELHA", "BAGA AZUL", "BAGA VERDE",
    "%s   IDADE %lud", "toque no nome: renomear",
    "COMBATE", "ATQ", "DEF", "VEL", "PES", "TREINAR FORCA",
    "MEDALHAS %d/%d", "toque: voltar",
    "NOME:", "toque para voltar",
    "COM", "ALE", "ENE", "HIG",
    "REC %u",
    "PROGRESSO", "Niv.%u", "%u min para Niv.%u", "EVOLUCAO", "Forma final",
    "Pronto a evoluir!", "Tudo a 40 para evoluir",
    "Evolui em %u niv.", "Descuidos: %u",
    "SOM ON", "SOM OFF",
    "EVOLUIR", "%s quer dizer-te algo...", "%s sente-se abandonado...",
    "Evoluir?", "Manter forma", "Despedir?", "Adeus", "Ficar juntos",
    "Escolhe o inicial",
    "Sem sprites", "Carrega-os no SD",
    "PS", "IV %u",
    "MENU", "AJUSTES", "FECHAR", "EQUIPA %u/6", "EQUIPA", "- vazio -", "%s junta-se a equipa!", "Equipa cheia: quem substituir?", "Deixa-lo ir",
    "STATS", "TREINO", "FORCA", "VELOCIDADE", "DEFESA", "Sobe sozinha se estiver bem",
    "GOLPES", "- vazio -", "Escolhe um golpe", "Toca para mudar", "POT %u", "ESTADO",
    "%s quer aprender", "Nao aprender",
    "%s usa %s", "Super eficaz!", "Pouco eficaz...", "Nao teve efeito...",
    "%s falhou!", "Acerto critico!", "%s desmaiou!", "Feriu-se!",
    "%s: %s", "PARALISIA", "QUEIMADURA", "VENENO", "A DORMIR", "CONGELADO", "CONFUSAO",
    "Ganhaste!", "Perdeste...",
    "%s envia %s", "Vai, %s!", "GINASIOS", "MEDALHAS %u/8", "TREINADOR", "VELOCIDADE +%u", "toca: mudar avatar", "%u no total", "NORMAL", "DIFICIL", "ESCOLHIDOS %u/%u", "LUTAR", "BLOQUEADO", "POKEMON", "%s derrotado!", "NOVA MEDALHA!", "VOL %u", "CAIXA %u/%u", "trocar com %s: escolhe", "CAIXA", "TRAZER", "so com um ovo", "COMBATE LAN", "CRIAR", "ENTRAR", "a procurar...", "pronto!", "versao diferente", "criar ou entrar", "rival: %u mons", "o rival saiu", "a esperar pelo rival...", "OUTRA VEZ", "FUGIR", "de que regiao vem o ovo", "%s +%u", "ja nao pode treinar mais", "ESCOLHE A REGIAO", "REFORMAR", "Reformar agora?", "o proximo evolui um dia depois", "evolui um dia depois",
   "FALTA PACK", "SOLTAR", "vai para sempre", "A EQUIPA", "nao entrara na equipa",
    "MOCHILA", "MOCHILA VAZIA", "EXPLORAR", "Um %s selvagem aparece!", "%s fugiu!",
    "Conseguiste fugir!", "Nao conseguiste fugir!", "Lancas uma %s", "%s capturado!", "Escapou!",
    "Usas %s", "Sem efeito", "Encontras %s!", "CRIAR ESTE", "A CRIAR",
    "SAIR", "Sair da luta?",
    "derrotado: %u vez", "derrotado: %u vezes", "perdeste: %u vez", "perdeste: %u vezes",
    "POKE MART", "1 passo = $1", "teus passos de sempre: %lu", "Wallet: $%lu", "Comprar %s?", "CUSTO: $%lu", },
};

// Nombres de medalla en sus tres longitudes [idioma][medalla].
static const char *const MED_NAME[LANG_COUNT][MED_COUNT] = {
  { "Nv.10", "Nv.25", "Nv.50", "BAYA", "RACHA 7", "VINCULO", "FORMA TOPE", "EN FORMA" },
  { "Lv.10", "Lv.25", "Lv.50", "BERRY", "7 STREAK", "BOND", "TOP FORM", "IN SHAPE" },
  { "Niv.10", "Niv.25", "Niv.50", "BAIE", "SERIE 7", "LIEN", "FORME MAX", "EN FORME" },
  { "Lv.10", "Lv.25", "Lv.50", "BEERE", "7 SERIE", "BINDUNG", "ENDFORM", "FIT" },
  { "Lv.10", "Lv.25", "Lv.50", "BACCA", "SERIE 7", "LEGAME", "FORMA MAX", "IN FORMA" },
  { "Niv.10", "Niv.25", "Niv.50", "BAGA", "SEQ 7", "LACO", "FORMA MAX", "EM FORMA" },
};
static const char *const MED_LBL[LANG_COUNT][MED_COUNT] = {
  { "Nv10", "Nv25", "Nv50", "BAYA", "7DIAS", "VINC", "TOPE", "SANO" },
  { "Lv10", "Lv25", "Lv50", "BERRY", "7DAYS", "BOND", "TOP", "FIT" },
  { "Niv10", "Niv25", "Niv50", "BAIE", "7JRS", "LIEN", "MAX", "FORME" },
  { "Lv10", "Lv25", "Lv50", "BEERE", "7TAGE", "BND", "END", "FIT" },
  { "Lv10", "Lv25", "Lv50", "BACCA", "7GG", "LEG", "MAX", "FIT" },
  { "Niv10", "Niv25", "Niv50", "BAGA", "7DIAS", "LACO", "MAX", "FIT" },
};
static const char *const MED_DSC[LANG_COUNT][MED_COUNT] = {
  { "NIVEL 10", "NIVEL 25", "NIVEL 50", "BAYA HALLADA",
    "RACHA 7 DIAS", "VINCULO MAX", "FORMA FINAL", "EN FORMA" },
  { "LEVEL 10", "LEVEL 25", "LEVEL 50", "BERRY FOUND",
    "7 DAY STREAK", "MAX BOND", "FINAL FORM", "IN SHAPE" },
  { "NIVEAU 10", "NIVEAU 25", "NIVEAU 50", "BAIE TROUVEE",
    "SERIE 7 JOURS", "LIEN MAX", "FORME FINALE", "EN FORME" },
  { "LEVEL 10", "LEVEL 25", "LEVEL 50", "BEERE GEFUNDEN",
    "7 TAGE SERIE", "MAX BINDUNG", "ENDFORM", "FIT" },
  { "LIVELLO 10", "LIVELLO 25", "LIVELLO 50", "BACCA TROVATA",
    "SERIE 7 GIORNI", "LEGAME MAX", "FORMA FINALE", "IN FORMA" },
  { "NIVEL 10", "NIVEL 25", "NIVEL 50", "BAGA ACHADA",
    "SEQ 7 DIAS", "LACO MAX", "FORMA FINAL", "EM FORMA" },
};

// German species names in National-Dex order. Generated from
// https://github.com/sindresorhus/pokemon/blob/main/data/de.json
// The stock bitmap font only supports ASCII: ae/oe/ue, ss, and e for accents.
// Indices are stable: no game data or save data is translated.
static const char *const POKEMON_NAMES_DE[DEX_COUNT + 1] = {
  "?",  // #0 unused
  "BISASAM",  // #1: Bisasam
  "BISAKNOSP",  // #2: Bisaknosp
  "BISAFLOR",  // #3: Bisaflor
  "GLUMANDA",  // #4: Glumanda
  "GLUTEXO",  // #5: Glutexo
  "GLURAK",  // #6: Glurak
  "SCHIGGY",  // #7: Schiggy
  "SCHILLOK",  // #8: Schillok
  "TURTOK",  // #9: Turtok
  "RAUPY",  // #10: Raupy
  "SAFCON",  // #11: Safcon
  "SMETTBO",  // #12: Smettbo
  "HORNLIU",  // #13: Hornliu
  "KOKUNA",  // #14: Kokuna
  "BIBOR",  // #15: Bibor
  "TAUBSI",  // #16: Taubsi
  "TAUBOGA",  // #17: Tauboga
  "TAUBOSS",  // #18: Tauboss
  "RATTFRATZ",  // #19: Rattfratz
  "RATTIKARL",  // #20: Rattikarl
  "HABITAK",  // #21: Habitak
  "IBITAK",  // #22: Ibitak
  "RETTAN",  // #23: Rettan
  "ARBOK",  // #24: Arbok
  "PIKACHU",  // #25: Pikachu
  "RAICHU",  // #26: Raichu
  "SANDAN",  // #27: Sandan
  "SANDAMER",  // #28: Sandamer
  "NIDORAN W",  // #29: Nidoran♀
  "NIDORINA",  // #30: Nidorina
  "NIDOQUEEN",  // #31: Nidoqueen
  "NIDORAN M",  // #32: Nidoran♂
  "NIDORINO",  // #33: Nidorino
  "NIDOKING",  // #34: Nidoking
  "PIEPI",  // #35: Piepi
  "PIXI",  // #36: Pixi
  "VULPIX",  // #37: Vulpix
  "VULNONA",  // #38: Vulnona
  "PUMMELUFF",  // #39: Pummeluff
  "KNUDDELUFF",  // #40: Knuddeluff
  "ZUBAT",  // #41: Zubat
  "GOLBAT",  // #42: Golbat
  "MYRAPLA",  // #43: Myrapla
  "DUFLOR",  // #44: Duflor
  "GIFLOR",  // #45: Giflor
  "PARAS",  // #46: Paras
  "PARASEK",  // #47: Parasek
  "BLUZUK",  // #48: Bluzuk
  "OMOT",  // #49: Omot
  "DIGDA",  // #50: Digda
  "DIGDRI",  // #51: Digdri
  "MAUZI",  // #52: Mauzi
  "SNOBILIKAT",  // #53: Snobilikat
  "ENTON",  // #54: Enton
  "ENTORON",  // #55: Entoron
  "MENKI",  // #56: Menki
  "RASAFF",  // #57: Rasaff
  "FUKANO",  // #58: Fukano
  "ARKANI",  // #59: Arkani
  "QUAPSEL",  // #60: Quapsel
  "QUAPUTZI",  // #61: Quaputzi
  "QUAPPO",  // #62: Quappo
  "ABRA",  // #63: Abra
  "KADABRA",  // #64: Kadabra
  "SIMSALA",  // #65: Simsala
  "MACHOLLO",  // #66: Machollo
  "MASCHOCK",  // #67: Maschock
  "MACHOMEI",  // #68: Machomei
  "KNOFENSA",  // #69: Knofensa
  "ULTRIGARIA",  // #70: Ultrigaria
  "SARZENIA",  // #71: Sarzenia
  "TENTACHA",  // #72: Tentacha
  "TENTOXA",  // #73: Tentoxa
  "KLEINSTEIN",  // #74: Kleinstein
  "GEOROK",  // #75: Georok
  "GEOWAZ",  // #76: Geowaz
  "PONITA",  // #77: Ponita
  "GALLOPA",  // #78: Gallopa
  "FLEGMON",  // #79: Flegmon
  "LAHMUS",  // #80: Lahmus
  "MAGNETILO",  // #81: Magnetilo
  "MAGNETON",  // #82: Magneton
  "PORENTA",  // #83: Porenta
  "DODU",  // #84: Dodu
  "DODRI",  // #85: Dodri
  "JUROB",  // #86: Jurob
  "JUGONG",  // #87: Jugong
  "SLEIMA",  // #88: Sleima
  "SLEIMOK",  // #89: Sleimok
  "MUSCHAS",  // #90: Muschas
  "AUSTOS",  // #91: Austos
  "NEBULAK",  // #92: Nebulak
  "ALPOLLO",  // #93: Alpollo
  "GENGAR",  // #94: Gengar
  "ONIX",  // #95: Onix
  "TRAUMATO",  // #96: Traumato
  "HYPNO",  // #97: Hypno
  "KRABBY",  // #98: Krabby
  "KINGLER",  // #99: Kingler
  "VOLTOBAL",  // #100: Voltobal
  "LEKTROBAL",  // #101: Lektrobal
  "OWEI",  // #102: Owei
  "KOKOWEI",  // #103: Kokowei
  "TRAGOSSO",  // #104: Tragosso
  "KNOGGA",  // #105: Knogga
  "KICKLEE",  // #106: Kicklee
  "NOCKCHAN",  // #107: Nockchan
  "SCHLURP",  // #108: Schlurp
  "SMOGON",  // #109: Smogon
  "SMOGMOG",  // #110: Smogmog
  "RIHORN",  // #111: Rihorn
  "RIZEROS",  // #112: Rizeros
  "CHANEIRA",  // #113: Chaneira
  "TANGELA",  // #114: Tangela
  "KANGAMA",  // #115: Kangama
  "SEEPER",  // #116: Seeper
  "SEEMON",  // #117: Seemon
  "GOLDINI",  // #118: Goldini
  "GOLKING",  // #119: Golking
  "STERNDU",  // #120: Sterndu
  "STARMIE",  // #121: Starmie
  "PANTIMOS",  // #122: Pantimos
  "SICHLOR",  // #123: Sichlor
  "ROSSANA",  // #124: Rossana
  "ELEKTEK",  // #125: Elektek
  "MAGMAR",  // #126: Magmar
  "PINSIR",  // #127: Pinsir
  "TAUROS",  // #128: Tauros
  "KARPADOR",  // #129: Karpador
  "GARADOS",  // #130: Garados
  "LAPRAS",  // #131: Lapras
  "DITTO",  // #132: Ditto
  "EVOLI",  // #133: Evoli
  "AQUANA",  // #134: Aquana
  "BLITZA",  // #135: Blitza
  "FLAMARA",  // #136: Flamara
  "PORYGON",  // #137: Porygon
  "AMONITAS",  // #138: Amonitas
  "AMOROSO",  // #139: Amoroso
  "KABUTO",  // #140: Kabuto
  "KABUTOPS",  // #141: Kabutops
  "AERODACTYL",  // #142: Aerodactyl
  "RELAXO",  // #143: Relaxo
  "ARKTOS",  // #144: Arktos
  "ZAPDOS",  // #145: Zapdos
  "LAVADOS",  // #146: Lavados
  "DRATINI",  // #147: Dratini
  "DRAGONIR",  // #148: Dragonir
  "DRAGORAN",  // #149: Dragoran
  "MEWTU",  // #150: Mewtu
  "MEW",  // #151: Mew
  "ENDIVIE",  // #152: Endivie
  "LORBLATT",  // #153: Lorblatt
  "MEGANIE",  // #154: Meganie
  "FEURIGEL",  // #155: Feurigel
  "IGELAVAR",  // #156: Igelavar
  "TORNUPTO",  // #157: Tornupto
  "KARNIMANI",  // #158: Karnimani
  "TYRACROC",  // #159: Tyracroc
  "IMPERGATOR",  // #160: Impergator
  "WIESOR",  // #161: Wiesor
  "WIESENIOR",  // #162: Wiesenior
  "HOOTHOOT",  // #163: Hoothoot
  "NOCTUH",  // #164: Noctuh
  "LEDYBA",  // #165: Ledyba
  "LEDIAN",  // #166: Ledian
  "WEBARAK",  // #167: Webarak
  "ARIADOS",  // #168: Ariados
  "IKSBAT",  // #169: Iksbat
  "LAMPI",  // #170: Lampi
  "LANTURN",  // #171: Lanturn
  "PICHU",  // #172: Pichu
  "PII",  // #173: Pii
  "FLUFFELUFF",  // #174: Fluffeluff
  "TOGEPI",  // #175: Togepi
  "TOGETIC",  // #176: Togetic
  "NATU",  // #177: Natu
  "XATU",  // #178: Xatu
  "VOLTILAMM",  // #179: Voltilamm
  "WAATY",  // #180: Waaty
  "AMPHAROS",  // #181: Ampharos
  "BLUBELLA",  // #182: Blubella
  "MARILL",  // #183: Marill
  "AZUMARILL",  // #184: Azumarill
  "MOGELBAUM",  // #185: Mogelbaum
  "QUAXO",  // #186: Quaxo
  "HOPPSPROSS",  // #187: Hoppspross
  "HUBELUPF",  // #188: Hubelupf
  "PAPUNGHA",  // #189: Papungha
  "GRIFFEL",  // #190: Griffel
  "SONNKERN",  // #191: Sonnkern
  "SONNFLORA",  // #192: Sonnflora
  "YANMA",  // #193: Yanma
  "FELINO",  // #194: Felino
  "MORLORD",  // #195: Morlord
  "PSIANA",  // #196: Psiana
  "NACHTARA",  // #197: Nachtara
  "KRAMURX",  // #198: Kramurx
  "LASCHOKING",  // #199: Laschoking
  "TRAUNFUGIL",  // #200: Traunfugil
  "ICOGNITO",  // #201: Icognito
  "WOINGENAU",  // #202: Woingenau
  "GIRAFARIG",  // #203: Girafarig
  "TANNZA",  // #204: Tannza
  "FORSTELLKA",  // #205: Forstellka
  "DUMMISEL",  // #206: Dummisel
  "SKORGLA",  // #207: Skorgla
  "STAHLOS",  // #208: Stahlos
  "SNUBBULL",  // #209: Snubbull
  "GRANBULL",  // #210: Granbull
  "BALDORFISH",  // #211: Baldorfish
  "SCHEROX",  // #212: Scherox
  "POTTROTT",  // #213: Pottrott
  "SKARABORN",  // #214: Skaraborn
  "SNIEBEL",  // #215: Sniebel
  "TEDDIURSA",  // #216: Teddiursa
  "URSARING",  // #217: Ursaring
  "SCHNECKMAG",  // #218: Schneckmag
  "MAGCARGO",  // #219: Magcargo
  "QUIEKEL",  // #220: Quiekel
  "KEIFEL",  // #221: Keifel
  "CORASONN",  // #222: Corasonn
  "REMORAID",  // #223: Remoraid
  "OCTILLERY",  // #224: Octillery
  "BOTOGEL",  // #225: Botogel
  "MANTAX",  // #226: Mantax
  "PANZAERON",  // #227: Panzaeron
  "HUNDUSTER",  // #228: Hunduster
  "HUNDEMON",  // #229: Hundemon
  "SEEDRAKING",  // #230: Seedraking
  "PHANPY",  // #231: Phanpy
  "DONPHAN",  // #232: Donphan
  "PORYGON2",  // #233: Porygon2
  "DAMHIRPLEX",  // #234: Damhirplex
  "FARBEAGLE",  // #235: Farbeagle
  "RABAUZ",  // #236: Rabauz
  "KAPOERA",  // #237: Kapoera
  "KUSSILLA",  // #238: Kussilla
  "ELEKID",  // #239: Elekid
  "MAGBY",  // #240: Magby
  "MILTANK",  // #241: Miltank
  "HEITEIRA",  // #242: Heiteira
  "RAIKOU",  // #243: Raikou
  "ENTEI",  // #244: Entei
  "SUICUNE",  // #245: Suicune
  "LARVITAR",  // #246: Larvitar
  "PUPITAR",  // #247: Pupitar
  "DESPOTAR",  // #248: Despotar
  "LUGIA",  // #249: Lugia
  "HO-OH",  // #250: Ho-Oh
  "CELEBI",  // #251: Celebi
  "GECKARBOR",  // #252: Geckarbor
  "REPTAIN",  // #253: Reptain
  "GEWALDRO",  // #254: Gewaldro
  "FLEMMLI",  // #255: Flemmli
  "JUNGGLUT",  // #256: Jungglut
  "LOHGOCK",  // #257: Lohgock
  "HYDROPI",  // #258: Hydropi
  "MOORABBEL",  // #259: Moorabbel
  "SUMPEX",  // #260: Sumpex
  "FIFFYEN",  // #261: Fiffyen
  "MAGNAYEN",  // #262: Magnayen
  "ZIGZACHS",  // #263: Zigzachs
  "GERADAKS",  // #264: Geradaks
  "WAUMPEL",  // #265: Waumpel
  "SCHALOKO",  // #266: Schaloko
  "PAPINELLA",  // #267: Papinella
  "PANEKON",  // #268: Panekon
  "PUDOX",  // #269: Pudox
  "LOTURZEL",  // #270: Loturzel
  "LOMBRERO",  // #271: Lombrero
  "KAPPALORES",  // #272: Kappalores
  "SAMURZEL",  // #273: Samurzel
  "BLANAS",  // #274: Blanas
  "TENGULIST",  // #275: Tengulist
  "SCHWALBINI",  // #276: Schwalbini
  "SCHWALBOSS",  // #277: Schwalboss
  "WINGULL",  // #278: Wingull
  "PELIPPER",  // #279: Pelipper
  "TRASLA",  // #280: Trasla
  "KIRLIA",  // #281: Kirlia
  "GUARDEVOIR",  // #282: Guardevoir
  "GEHWEIHER",  // #283: Gehweiher
  "MASKEREGEN",  // #284: Maskeregen
  "KNILZ",  // #285: Knilz
  "KAPILZ",  // #286: Kapilz
  "BUMMELZ",  // #287: Bummelz
  "MUNTIER",  // #288: Muntier
  "LETARKING",  // #289: Letarking
  "NINCADA",  // #290: Nincada
  "NINJASK",  // #291: Ninjask
  "NINJATOM",  // #292: Ninjatom
  "FLURMEL",  // #293: Flurmel
  "KRAKEELO",  // #294: Krakeelo
  "KRAWUMMS",  // #295: Krawumms
  "MAKUHITA",  // #296: Makuhita
  "HARIYAMA",  // #297: Hariyama
  "AZURILL",  // #298: Azurill
  "NASGNET",  // #299: Nasgnet
  "ENECO",  // #300: Eneco
  "ENEKORO",  // #301: Enekoro
  "ZOBIRIS",  // #302: Zobiris
  "FLUNKIFER",  // #303: Flunkifer
  "STOLLUNIOR",  // #304: Stollunior
  "STOLLRAK",  // #305: Stollrak
  "STOLLOSS",  // #306: Stolloss
  "MEDITIE",  // #307: Meditie
  "MEDITALIS",  // #308: Meditalis
  "FRIZELBLIZ",  // #309: Frizelbliz
  "VOLTENSO",  // #310: Voltenso
  "PLUSLE",  // #311: Plusle
  "MINUN",  // #312: Minun
  "VOLBEAT",  // #313: Volbeat
  "ILLUMISE",  // #314: Illumise
  "ROSELIA",  // #315: Roselia
  "SCHLUPPUCK",  // #316: Schluppuck
  "SCHLUKWECH",  // #317: Schlukwech
  "KANIVANHA",  // #318: Kanivanha
  "TOHAIDO",  // #319: Tohaido
  "WAILMER",  // #320: Wailmer
  "WAILORD",  // #321: Wailord
  "CAMAUB",  // #322: Camaub
  "CAMERUPT",  // #323: Camerupt
  "QURTEL",  // #324: Qurtel
  "SPOINK",  // #325: Spoink
  "GROINK",  // #326: Groink
  "PANDIR",  // #327: Pandir
  "KNACKLION",  // #328: Knacklion
  "VIBRAVA",  // #329: Vibrava
  "LIBELLDRA",  // #330: Libelldra
  "TUSKA",  // #331: Tuska
  "NOKTUSKA",  // #332: Noktuska
  "WABLU",  // #333: Wablu
  "ALTARIA",  // #334: Altaria
  "SENGO",  // #335: Sengo
  "VIPITIS",  // #336: Vipitis
  "LUNASTEIN",  // #337: Lunastein
  "SONNFEL",  // #338: Sonnfel
  "SCHMERBE",  // #339: Schmerbe
  "WELSAR",  // #340: Welsar
  "KREBSCORPS",  // #341: Krebscorps
  "KREBUTACK",  // #342: Krebutack
  "PUPPANCE",  // #343: Puppance
  "LEPUMENTAS",  // #344: Lepumentas
  "LILIEP",  // #345: Liliep
  "WIELIE",  // #346: Wielie
  "ANORITH",  // #347: Anorith
  "ARMALDO",  // #348: Armaldo
  "BARSCHWA",  // #349: Barschwa
  "MILOTIC",  // #350: Milotic
  "FORMEO",  // #351: Formeo
  "KECLEON",  // #352: Kecleon
  "SHUPPET",  // #353: Shuppet
  "BANETTE",  // #354: Banette
  "ZWIRRLICHT",  // #355: Zwirrlicht
  "ZWIRRKLOP",  // #356: Zwirrklop
  "TROPIUS",  // #357: Tropius
  "PALIMPALIM",  // #358: Palimpalim
  "ABSOL",  // #359: Absol
  "ISSO",  // #360: Isso
  "SCHNEPPKE",  // #361: Schneppke
  "FIRNONTOR",  // #362: Firnontor
  "SEEMOPS",  // #363: Seemops
  "SEEJONG",  // #364: Seejong
  "WALRAISA",  // #365: Walraisa
  "PERLU",  // #366: Perlu
  "AALABYSS",  // #367: Aalabyss
  "SAGANABYSS",  // #368: Saganabyss
  "RELICANTH",  // #369: Relicanth
  "LIEBISKUS",  // #370: Liebiskus
  "KINDWURM",  // #371: Kindwurm
  "DRASCHEL",  // #372: Draschel
  "BRUTALANDA",  // #373: Brutalanda
  "TANHEL",  // #374: Tanhel
  "METANG",  // #375: Metang
  "METAGROSS",  // #376: Metagross
  "REGIROCK",  // #377: Regirock
  "REGICE",  // #378: Regice
  "REGISTEEL",  // #379: Registeel
  "LATIAS",  // #380: Latias
  "LATIOS",  // #381: Latios
  "KYOGRE",  // #382: Kyogre
  "GROUDON",  // #383: Groudon
  "RAYQUAZA",  // #384: Rayquaza
  "JIRACHI",  // #385: Jirachi
  "DEOXYS",  // #386: Deoxys
  "CHELAST",  // #387: Chelast
  "CHELCARAIN",  // #388: Chelcarain
  "CHELTERRAR",  // #389: Chelterrar
  "PANFLAM",  // #390: Panflam
  "PANPYRO",  // #391: Panpyro
  "PANFERNO",  // #392: Panferno
  "PLINFA",  // #393: Plinfa
  "PLIPRIN",  // #394: Pliprin
  "IMPOLEON",  // #395: Impoleon
  "STARALILI",  // #396: Staralili
  "STARAVIA",  // #397: Staravia
  "STARAPTOR",  // #398: Staraptor
  "BIDIZA",  // #399: Bidiza
  "BIDIFAS",  // #400: Bidifas
  "ZIRPURZE",  // #401: Zirpurze
  "ZIRPEISE",  // #402: Zirpeise
  "SHEINUX",  // #403: Sheinux
  "LUXIO",  // #404: Luxio
  "LUXTRA",  // #405: Luxtra
  "KNOSPI",  // #406: Knospi
  "ROSERADE",  // #407: Roserade
  "KOKNODON",  // #408: Koknodon
  "RAMEIDON",  // #409: Rameidon
  "SCHILTERUS",  // #410: Schilterus
  "BOLLTERUS",  // #411: Bollterus
  "BURMY",  // #412: Burmy
  "BURMADAME",  // #413: Burmadame
  "MOTERPEL",  // #414: Moterpel
  "WADRIBIE",  // #415: Wadribie
  "HONWEISEL",  // #416: Honweisel
  "PACHIRISU",  // #417: Pachirisu
  "BAMELIN",  // #418: Bamelin
  "BOJELIN",  // #419: Bojelin
  "KIKUGI",  // #420: Kikugi
  "KINOSO",  // #421: Kinoso
  "SCHALELLOS",  // #422: Schalellos
  "GASTRODON",  // #423: Gastrodon
  "AMBIDIFFEL",  // #424: Ambidiffel
  "DRIFTLON",  // #425: Driftlon
  "DRIFZEPELI",  // #426: Drifzepeli
  "HASPIROR",  // #427: Haspiror
  "SCHLAPOR",  // #428: Schlapor
  "TRAUNMAGIL",  // #429: Traunmagil
  "KRAMSHEF",  // #430: Kramshef
  "CHARMIAN",  // #431: Charmian
  "SHNURGARST",  // #432: Shnurgarst
  "KLINGPLIM",  // #433: Klingplim
  "SKUNKAPUH",  // #434: Skunkapuh
  "SKUNTANK",  // #435: Skuntank
  "BRONZEL",  // #436: Bronzel
  "BRONZONG",  // #437: Bronzong
  "MOBAI",  // #438: Mobai
  "PANTIMIMI",  // #439: Pantimimi
  "WONNEIRA",  // #440: Wonneira
  "PLAUDAGEI",  // #441: Plaudagei
  "KRYPPUK",  // #442: Kryppuk
  "KAUMALAT",  // #443: Kaumalat
  "KNARKSEL",  // #444: Knarksel
  "KNAKRACK",  // #445: Knakrack
  "MAMPFAXO",  // #446: Mampfaxo
  "RIOLU",  // #447: Riolu
  "LUCARIO",  // #448: Lucario
  "HIPPOPOTAS",  // #449: Hippopotas
  "HIPPOTERUS",  // #450: Hippoterus
  "PIONSKORA",  // #451: Pionskora
  "PIONDRAGI",  // #452: Piondragi
  "GLIBUNKEL",  // #453: Glibunkel
  "TOXIQUAK",  // #454: Toxiquak
  "VENUFLIBIS",  // #455: Venuflibis
  "FINNEON",  // #456: Finneon
  "LUMINEON",  // #457: Lumineon
  "MANTIRPS",  // #458: Mantirps
  "SHNEBEDECK",  // #459: Shnebedeck
  "REXBLISAR",  // #460: Rexblisar
  "SNIBUNNA",  // #461: Snibunna
  "MAGNEZONE",  // #462: Magnezone
  "SCHLURPLEK",  // #463: Schlurplek
  "RIHORNIOR",  // #464: Rihornior
  "TANGOLOSS",  // #465: Tangoloss
  "ELEVOLTEK",  // #466: Elevoltek
  "MAGBRANT",  // #467: Magbrant
  "TOGEKISS",  // #468: Togekiss
  "YANMEGA",  // #469: Yanmega
  "FOLIPURBA",  // #470: Folipurba
  "GLAZIOLA",  // #471: Glaziola
  "SKORGRO",  // #472: Skorgro
  "MAMUTEL",  // #473: Mamutel
  "PORYGON-Z",  // #474: Porygon-Z
  "GALAGLADI",  // #475: Galagladi
  "VOLUMINAS",  // #476: Voluminas
  "ZWIRRFINST",  // #477: Zwirrfinst
  "FROSDEDJE",  // #478: Frosdedje
  "ROTOM",  // #479: Rotom
  "SELFE",  // #480: Selfe
  "VESPRIT",  // #481: Vesprit
  "TOBUTZ",  // #482: Tobutz
  "DIALGA",  // #483: Dialga
  "PALKIA",  // #484: Palkia
  "HEATRAN",  // #485: Heatran
  "REGIGIGAS",  // #486: Regigigas
  "GIRATINA",  // #487: Giratina
  "CRESSELIA",  // #488: Cresselia
  "PHIONE",  // #489: Phione
  "MANAPHY",  // #490: Manaphy
  "DARKRAI",  // #491: Darkrai
  "SHAYMIN",  // #492: Shaymin
  "ARCEUS",  // #493: Arceus
  "VICTINI",  // #494: Victini
  "SERPIFEU",  // #495: Serpifeu
  "EFOSERP",  // #496: Efoserp
  "SERPIROYAL",  // #497: Serpiroyal
  "FLOINK",  // #498: Floink
  "FERKOKEL",  // #499: Ferkokel
  "FLAMBIREX",  // #500: Flambirex
  "OTTARO",  // #501: Ottaro
  "ZWOTTRONIN",  // #502: Zwottronin
  "ADMURAI",  // #503: Admurai
  "NAGELOTZ",  // #504: Nagelotz
  "KUKMARDA",  // #505: Kukmarda
  "YORKLEFF",  // #506: Yorkleff
  "TERRIBARK",  // #507: Terribark
  "BISSBARK",  // #508: Bissbark
  "FELILOU",  // #509: Felilou
  "KLEOPARDA",  // #510: Kleoparda
  "VEGIMAK",  // #511: Vegimak
  "VEGICHITA",  // #512: Vegichita
  "GRILLMAK",  // #513: Grillmak
  "GRILLCHITA",  // #514: Grillchita
  "SODAMAK",  // #515: Sodamak
  "SODACHITA",  // #516: Sodachita
  "SOMNIAM",  // #517: Somniam
  "SOMNIVORA",  // #518: Somnivora
  "DUSSELGURR",  // #519: Dusselgurr
  "NAVITAUB",  // #520: Navitaub
  "FASASNOB",  // #521: Fasasnob
  "ELEZEBA",  // #522: Elezeba
  "ZEBRITZ",  // #523: Zebritz
  "KIESLING",  // #524: Kiesling
  "SEDIMANTUR",  // #525: Sedimantur
  "BROCKOLOSS",  // #526: Brockoloss
  "FLEKNOIL",  // #527: Fleknoil
  "FLETIAMO",  // #528: Fletiamo
  "ROTOMURF",  // #529: Rotomurf
  "STALOBOR",  // #530: Stalobor
  "OHRDOCH",  // #531: Ohrdoch
  "PRAKTIBALK",  // #532: Praktibalk
  "STREPOLI",  // #533: Strepoli
  "MEISTAGRIF",  // #534: Meistagrif
  "SCHALLQUAP",  // #535: Schallquap
  "MEBRANA",  // #536: Mebrana
  "BRANAWARZ",  // #537: Branawarz
  "JIUTESTO",  // #538: Jiutesto
  "KARADONIS",  // #539: Karadonis
  "STRAWICKL",  // #540: Strawickl
  "FOLIKON",  // #541: Folikon
  "MATRIFOL",  // #542: Matrifol
  "TOXIPED",  // #543: Toxiped
  "ROLLUM",  // #544: Rollum
  "CERAPENDRA",  // #545: Cerapendra
  "WAUMBOLL",  // #546: Waumboll
  "ELFUN",  // #547: Elfun
  "LILMINIP",  // #548: Lilminip
  "DRESSELLA",  // #549: Dressella
  "BARSCHUFT",  // #550: Barschuft
  "GANOVIL",  // #551: Ganovil
  "ROKKAIMAN",  // #552: Rokkaiman
  "RABIGATOR",  // #553: Rabigator
  "FLAMPION",  // #554: Flampion
  "FLAMPIVIAN",  // #555: Flampivian
  "MARACAMBA",  // #556: Maracamba
  "LITHOMITH",  // #557: Lithomith
  "CASTELLITH",  // #558: Castellith
  "ZURROKEX",  // #559: Zurrokex
  "IROKEX",  // #560: Irokex
  "SYMVOLARA",  // #561: Symvolara
  "MAKABAJA",  // #562: Makabaja
  "ECHNATOLL",  // #563: Echnatoll
  "GALAPAFLOS",  // #564: Galapaflos
  "KARIPPAS",  // #565: Karippas
  "FLAPTERYX",  // #566: Flapteryx
  "AEROPTERYX",  // #567: Aeropteryx
  "UNRATUETOX",  // #568: Unratütox
  "DEPONITOX",  // #569: Deponitox
  "ZORUA",  // #570: Zorua
  "ZOROARK",  // #571: Zoroark
  "PICOCHILLA",  // #572: Picochilla
  "CHILLABELL",  // #573: Chillabell
  "MOLLIMORBA",  // #574: Mollimorba
  "HYPNOMORBA",  // #575: Hypnomorba
  "MORBITESSE",  // #576: Morbitesse
  "MONOZYTO",  // #577: Monozyto
  "MITODOS",  // #578: Mitodos
  "ZYTOMEGA",  // #579: Zytomega
  "PICCOLENTE",  // #580: Piccolente
  "SWARONESS",  // #581: Swaroness
  "GELATINI",  // #582: Gelatini
  "GELATROPPO",  // #583: Gelatroppo
  "GELATWINO",  // #584: Gelatwino
  "SESOKITZ",  // #585: Sesokitz
  "KRONJUWILD",  // #586: Kronjuwild
  "EMOLGA",  // #587: Emolga
  "LAUKAPS",  // #588: Laukaps
  "CAVALANZAS",  // #589: Cavalanzas
  "TARNPIGNON",  // #590: Tarnpignon
  "HUTSASSA",  // #591: Hutsassa
  "QUABBEL",  // #592: Quabbel
  "APOQUALLYP",  // #593: Apoquallyp
  "MAMOLIDA",  // #594: Mamolida
  "WATTZAPF",  // #595: Wattzapf
  "VOLTULA",  // #596: Voltula
  "KASTADUR",  // #597: Kastadur
  "TENTANTEL",  // #598: Tentantel
  "KLIKK",  // #599: Klikk
  "KLIKLAK",  // #600: Kliklak
  "KLIKDIKLAK",  // #601: Klikdiklak
  "ZAPPLARDIN",  // #602: Zapplardin
  "ZAPPLALEK",  // #603: Zapplalek
  "ZAPPLARANG",  // #604: Zapplarang
  "PYGRAULON",  // #605: Pygraulon
  "MEGALON",  // #606: Megalon
  "LICHTEL",  // #607: Lichtel
  "LATERNECTO",  // #608: Laternecto
  "SKELABRA",  // #609: Skelabra
  "MILZA",  // #610: Milza
  "SHARFAX",  // #611: Sharfax
  "MAXAX",  // #612: Maxax
  "PETZNIEF",  // #613: Petznief
  "SIBERIO",  // #614: Siberio
  "FRIGOMETRI",  // #615: Frigometri
  "SCHNUTHELM",  // #616: Schnuthelm
  "HYDRAGIL",  // #617: Hydragil
  "FLUNSCHLIK",  // #618: Flunschlik
  "FU",  // #619: Fu
  "SHU",  // #620: Shu
  "SHARDRAGO",  // #621: Shardrago
  "GOLBIT",  // #622: Golbit
  "GOLGANTES",  // #623: Golgantes
  "GLADIANTRI",  // #624: Gladiantri
  "CAESURIO",  // #625: Caesurio
  "BISOFANK",  // #626: Bisofank
  "GERONIMATZ",  // #627: Geronimatz
  "WASHAKWIL",  // #628: Washakwil
  "SKALLYK",  // #629: Skallyk
  "GRYPHELDIS",  // #630: Grypheldis
  "FURNIFRASS",  // #631: Furnifraß
  "FERMICULA",  // #632: Fermicula
  "KAPUNO",  // #633: Kapuno
  "DUODINO",  // #634: Duodino
  "TRIKEPHALO",  // #635: Trikephalo
  "IGNIVOR",  // #636: Ignivor
  "RAMOTH",  // #637: Ramoth
  "KOBALIUM",  // #638: Kobalium
  "TERRAKIUM",  // #639: Terrakium
  "VIRIDIUM",  // #640: Viridium
  "BOREOS",  // #641: Boreos
  "VOLTOLOS",  // #642: Voltolos
  "RESHIRAM",  // #643: Reshiram
  "ZEKROM",  // #644: Zekrom
  "DEMETEROS",  // #645: Demeteros
  "KYUREM",  // #646: Kyurem
  "KELDEO",  // #647: Keldeo
  "MELOETTA",  // #648: Meloetta
  "GENESECT",  // #649: Genesect
  "IGAMARO",  // #650: Igamaro
  "IGASTARNISH",  // #651: Igastarnish
  "BRIGARON",  // #652: Brigaron
  "FYNX",  // #653: Fynx
  "RUTENA",  // #654: Rutena
  "FENNEXIS",  // #655: Fennexis
  "FROXY",  // #656: Froxy
  "AMPHIZEL",  // #657: Amphizel
  "QUAJUTSU",  // #658: Quajutsu
  "SCOPPEL",  // #659: Scoppel
  "GREBBIT",  // #660: Grebbit
  "DARTIRI",  // #661: Dartiri
  "DARTIGNIS",  // #662: Dartignis
  "FIARO",  // #663: Fiaro
  "PURMEL",  // #664: Purmel
  "PUPONCHO",  // #665: Puponcho
  "VIVILLON",  // #666: Vivillon
  "LEUFEO",  // #667: Leufeo
  "PYROLEO",  // #668: Pyroleo
  "FLABEBE",  // #669: Flabébé
  "FLOETTE",  // #670: Floette
  "FLORGES",  // #671: Florges
  "MAEHIKEL",  // #672: Mähikel
  "CHEVRUMM",  // #673: Chevrumm
  "PAM",  // #674: Pam
  "PANDAGRO",  // #675: Pandagro
  "COIFFWAFF",  // #676: Coiffwaff
  "PSIAU",  // #677: Psiau
  "PSIAUGON",  // #678: Psiaugon
  "GRAMOKLES",  // #679: Gramokles
  "DUOKLES",  // #680: Duokles
  "DURENGARD",  // #681: Durengard
  "PARFI",  // #682: Parfi
  "PARFINESSE",  // #683: Parfinesse
  "FLAUSCHLING",  // #684: Flauschling
  "SABBAIONE",  // #685: Sabbaione
  "ISCALAR",  // #686: Iscalar
  "CALAMANERO",  // #687: Calamanero
  "BITHORA",  // #688: Bithora
  "THANATHORA",  // #689: Thanathora
  "ALGITT",  // #690: Algitt
  "TANDRAK",  // #691: Tandrak
  "SCAMPISTO",  // #692: Scampisto
  "WUMMER",  // #693: Wummer
  "EGUANA",  // #694: Eguana
  "ELEZARD",  // #695: Elezard
  "BALGORAS",  // #696: Balgoras
  "MONARGORAS",  // #697: Monargoras
  "AMARINO",  // #698: Amarino
  "AMAGARGA",  // #699: Amagarga
  "FEELINARA",  // #700: Feelinara
  "RESLADERO",  // #701: Resladero
  "DEDENNE",  // #702: Dedenne
  "ROCARA",  // #703: Rocara
  "VISCORA",  // #704: Viscora
  "VISCARGOT",  // #705: Viscargot
  "VISCOGON",  // #706: Viscogon
  "CLAVION",  // #707: Clavion
  "PARAGONI",  // #708: Paragoni
  "TROMBORK",  // #709: Trombork
  "IRRBIS",  // #710: Irrbis
  "PUMPDJINN",  // #711: Pumpdjinn
  "ARKTIP",  // #712: Arktip
  "ARKTILAS",  // #713: Arktilas
  "EF-EM",  // #714: eF-eM
  "UHAFNIR",  // #715: UHaFnir
  "XERNEAS",  // #716: Xerneas
  "YVELTAL",  // #717: Yveltal
  "ZYGARDE",  // #718: Zygarde
  "DIANCIE",  // #719: Diancie
  "HOOPA",  // #720: Hoopa
  "VOLCANION",  // #721: Volcanion
  "BAUZ",  // #722: Bauz
  "ARBORETOSS",  // #723: Arboretoss
  "SILVARRO",  // #724: Silvarro
  "FLAMIAU",  // #725: Flamiau
  "MIEZUNDER",  // #726: Miezunder
  "FUEGRO",  // #727: Fuegro
  "ROBBALL",  // #728: Robball
  "MARIKECK",  // #729: Marikeck
  "PRIMARENE",  // #730: Primarene
  "PEPPECK",  // #731: Peppeck
  "TROMPECK",  // #732: Trompeck
  "TUKANON",  // #733: Tukanon
  "MANGUNIOR",  // #734: Mangunior
  "MANGUSPEKTOR",  // #735: Manguspektor
  "MABULA",  // #736: Mabula
  "AKKUP",  // #737: Akkup
  "DONARION",  // #738: Donarion
  "KRABBOX",  // #739: Krabbox
  "KRAWELL",  // #740: Krawell
  "CHOREOGEL",  // #741: Choreogel
  "WOMMEL",  // #742: Wommel
  "BANDELBY",  // #743: Bandelby
  "WUFFELS",  // #744: Wuffels
  "WOLWEROCK",  // #745: Wolwerock
  "LUSARDIN",  // #746: Lusardin
  "GARSTELLA",  // #747: Garstella
  "AGGROSTELLA",  // #748: Aggrostella
  "PAMPULI",  // #749: Pampuli
  "PAMPROSS",  // #750: Pampross
  "ARAQUA",  // #751: Araqua
  "ARANESTRO",  // #752: Aranestro
  "IMANTIS",  // #753: Imantis
  "MANTIDEA",  // #754: Mantidea
  "BUBUNGUS",  // #755: Bubungus
  "LAMELLUX",  // #756: Lamellux
  "MOLUNK",  // #757: Molunk
  "AMFIRA",  // #758: Amfira
  "VELURSI",  // #759: Velursi
  "KOSTURSO",  // #760: Kosturso
  "FRUBBERL",  // #761: Frubberl
  "FRUBAILA",  // #762: Frubaila
  "FRUYAL",  // #763: Fruyal
  "CURELEI",  // #764: Curelei
  "KOMMANDUTAN",  // #765: Kommandutan
  "QUARTERMAK",  // #766: Quartermak
  "REISSLAUS",  // #767: Reißlaus
  "TECTASS",  // #768: Tectass
  "SANKABUH",  // #769: Sankabuh
  "COLOSSAND",  // #770: Colossand
  "GUFA",  // #771: Gufa
  "TYP:NULL",  // #772: Typ:Null
  "AMIGENTO",  // #773: Amigento
  "METENO",  // #774: Meteno
  "KOALELU",  // #775: Koalelu
  "TORTUNATOR",  // #776: Tortunator
  "TOGEDEMARU",  // #777: Togedemaru
  "MIMIGMA",  // #778: Mimigma
  "KNIRFISH",  // #779: Knirfish
  "SEN-LONG",  // #780: Sen-Long
  "MORUDA",  // #781: Moruda
  "MINIRAS",  // #782: Miniras
  "MEDIRAS",  // #783: Mediras
  "GRANDIRAS",  // #784: Grandiras
  "KAPU-RIKI",  // #785: Kapu-Riki
  "KAPU-FALA",  // #786: Kapu-Fala
  "KAPU-TORO",  // #787: Kapu-Toro
  "KAPU-KIME",  // #788: Kapu-Kime
  "COSMOG",  // #789: Cosmog
  "COSMOVUM",  // #790: Cosmovum
  "SOLGALEO",  // #791: Solgaleo
  "LUNALA",  // #792: Lunala
  "ANEGO",  // #793: Anego
  "MASSKITO",  // #794: Masskito
  "SCHABELLE",  // #795: Schabelle
  "VOLTRIANT",  // #796: Voltriant
  "KAGURON",  // #797: Kaguron
  "KATAGAMI",  // #798: Katagami
  "SCHLINGKING",  // #799: Schlingking
  "NECROZMA",  // #800: Necrozma
  "MAGEARNA",  // #801: Magearna
  "MARSHADOW",  // #802: Marshadow
  "VENICRO",  // #803: Venicro
  "AGOYON",  // #804: Agoyon
  "MURAMURA",  // #805: Muramura
  "KOPPLOSIO",  // #806: Kopplosio
  "ZERAORA",  // #807: Zeraora
  "MELTAN",  // #808: Meltan
  "MELMETAL",  // #809: Melmetal
  "CHIMPEP",  // #810: Chimpep
  "CHIMSTIX",  // #811: Chimstix
  "GORTROM",  // #812: Gortrom
  "HOPPLO",  // #813: Hopplo
  "KICKERLO",  // #814: Kickerlo
  "LIBERLO",  // #815: Liberlo
  "MEMMEON",  // #816: Memmeon
  "PHLEGLEON",  // #817: Phlegleon
  "INTELLEON",  // #818: Intelleon
  "RAFFEL",  // #819: Raffel
  "SCHLARAFFEL",  // #820: Schlaraffel
  "MEIKRO",  // #821: Meikro
  "KRANOVIZ",  // #822: Kranoviz
  "KRARMOR",  // #823: Krarmor
  "SENSECT",  // #824: Sensect
  "KERADAR",  // #825: Keradar
  "MARITELLIT",  // #826: Maritellit
  "KLEPTIFUX",  // #827: Kleptifux
  "GAUNUX",  // #828: Gaunux
  "COTTINI",  // #829: Cottini
  "COTTOMI",  // #830: Cottomi
  "WOLLY",  // #831: Wolly
  "ZWOLLOCK",  // #832: Zwollock
  "KAMEHAPS",  // #833: Kamehaps
  "KAMALM",  // #834: Kamalm
  "VOLDI",  // #835: Voldi
  "BELLEKTRO",  // #836: Bellektro
  "KLONKETT",  // #837: Klonkett
  "WAGONG",  // #838: Wagong
  "MONTECARBO",  // #839: Montecarbo
  "KNAPFEL",  // #840: Knapfel
  "DRAPFEL",  // #841: Drapfel
  "SCHLAPFEL",  // #842: Schlapfel
  "SALANGA",  // #843: Salanga
  "SANACONDA",  // #844: Sanaconda
  "URGL",  // #845: Urgl
  "PIKUDA",  // #846: Pikuda
  "BARRAKIEFA",  // #847: Barrakiefa
  "TOXEL",  // #848: Toxel
  "RIFFEX",  // #849: Riffex
  "THERMOPOD",  // #850: Thermopod
  "INFERNOPOD",  // #851: Infernopod
  "KLOPPTOPUS",  // #852: Klopptopus
  "KAOCTO",  // #853: Kaocto
  "FATALITEE",  // #854: Fatalitee
  "MORTIPOT",  // #855: Mortipot
  "BRIMOVA",  // #856: Brimova
  "BRIMANO",  // #857: Brimano
  "SILEMBRIM",  // #858: Silembrim
  "BAEHMON",  // #859: Bähmon
  "PELZEBUB",  // #860: Pelzebub
  "OLANGAAR",  // #861: Olangaar
  "BARRIKADAX",  // #862: Barrikadax
  "MAUZINGER",  // #863: Mauzinger
  "GORGASONN",  // #864: Gorgasonn
  "LAUCHZELOT",  // #865: Lauchzelot
  "PANTIFROST",  // #866: Pantifrost
  "OGHNATOLL",  // #867: Oghnatoll
  "HOKUMIL",  // #868: Hokumil
  "POKUSAN",  // #869: Pokusan
  "LEGIOS",  // #870: Legios
  "BRITZIGEL",  // #871: Britzigel
  "SNOMNOM",  // #872: Snomnom
  "MOTTINEVA",  // #873: Mottineva
  "HUMANOLITH",  // #874: Humanolith
  "KUBUIN",  // #875: Kubuin
  "SERVOL",  // #876: Servol
  "MORPEKO",  // #877: Morpeko
  "KUPFANTI",  // #878: Kupfanti
  "PATINARAJA",  // #879: Patinaraja
  "LECTRAGON",  // #880: Lectragon
  "LECRYODON",  // #881: Lecryodon
  "PESCRAGON",  // #882: Pescragon
  "PESCRYODON",  // #883: Pescryodon
  "DURALUDON",  // #884: Duraludon
  "GROLLDRA",  // #885: Grolldra
  "PHANDRA",  // #886: Phandra
  "KATAPULDRA",  // #887: Katapuldra
  "ZACIAN",  // #888: Zacian
  "ZAMAZENTA",  // #889: Zamazenta
  "ENDYNALOS",  // #890: Endynalos
  "DAKUMA",  // #891: Dakuma
  "WULAOSU",  // #892: Wulaosu
  "ZARUDE",  // #893: Zarude
  "REGIELEKI",  // #894: Regieleki
  "REGIDRAGO",  // #895: Regidrago
  "POLAROSS",  // #896: Polaross
  "PHANTOROSS",  // #897: Phantoross
  "CORONOSPA",  // #898: Coronospa
  "DAMYTHIR",  // #899: Damythir
  "AXANTOR",  // #900: Axantor
  "URSALUNA",  // #901: Ursaluna
  "SALMAGNIS",  // #902: Salmagnis
  "SNIEBOSS",  // #903: Snieboss
  "MYRIADOR",  // #904: Myriador
  "CUPIDOS",  // #905: Cupidos
  "FELORI",  // #906: Felori
  "FELIOSPA",  // #907: Feliospa
  "MASKAGATO",  // #908: Maskagato
  "KROKEL",  // #909: Krokel
  "LOKROKO",  // #910: Lokroko
  "SKELOKROK",  // #911: Skelokrok
  "KWAKS",  // #912: Kwaks
  "FUENTENTE",  // #913: Fuentente
  "BAILONDA",  // #914: Bailonda
  "FERKULI",  // #915: Ferkuli
  "FRAGRUNZ",  // #916: Fragrunz
  "TARUNDEL",  // #917: Tarundel
  "SPINSIDIAS",  // #918: Spinsidias
  "MICRICK",  // #919: Micrick
  "LEXTREMO",  // #920: Lextremo
  "PAMO",  // #921: Pamo
  "PAMAMO",  // #922: Pamamo
  "PAMOMAMO",  // #923: Pamomamo
  "ZWIEPS",  // #924: Zwieps
  "FAMIEPS",  // #925: Famieps
  "HEFEL",  // #926: Hefel
  "BACKEL",  // #927: Backel
  "OLINI",  // #928: Olini
  "OLIVINIO",  // #929: Olivinio
  "OLITHENA",  // #930: Olithena
  "KRAWALLORO",  // #931: Krawalloro
  "GEOSALI",  // #932: Geosali
  "SEDISAL",  // #933: Sedisal
  "SALTIGANT",  // #934: Saltigant
  "KNARBON",  // #935: Knarbon
  "CRIMANZO",  // #936: Crimanzo
  "AZUGLADIS",  // #937: Azugladis
  "BLIPP",  // #938: Blipp
  "WAMPITZ",  // #939: Wampitz
  "VOLTREL",  // #940: Voltrel
  "VOLTREAN",  // #941: Voltrean
  "MOBTIFF",  // #942: Mobtiff
  "MASTIFIOSO",  // #943: Mastifioso
  "SPROXI",  // #944: Sproxi
  "AFFITI",  // #945: Affiti
  "WEHERBA",  // #946: Weherba
  "HORRERBA",  // #947: Horrerba
  "TENTAGRA",  // #948: Tentagra
  "TENTERRA",  // #949: Tenterra
  "KLIBBE",  // #950: Klibbe
  "CHILINGEL",  // #951: Chilingel
  "HALUPENJO",  // #952: Halupenjo
  "RELLUK",  // #953: Relluk
  "SKARABAKS",  // #954: Skarabaks
  "FLATTUTU",  // #955: Flattutu
  "PSIOPATRA",  // #956: Psiopatra
  "FORGITA",  // #957: Forgita
  "TAFFORGITA",  // #958: Tafforgita
  "GRANFORGITA",  // #959: Granforgita
  "SCHLIGDA",  // #960: Schligda
  "SCHLIGDRI",  // #961: Schligdri
  "ADEBOM",  // #962: Adebom
  "NORMIFIN",  // #963: Normifin
  "DELFINATOR",  // #964: Delfinator
  "KNATTOX",  // #965: Knattox
  "KNATTATOX",  // #966: Knattatox
  "MOPEX",  // #967: Mopex
  "SCHLURM",  // #968: Schlurm
  "LUMISPROSS",  // #969: Lumispross
  "LUMIFLORA",  // #970: Lumiflora
  "GRUFF",  // #971: Gruff
  "FRIEDWUFF",  // #972: Friedwuff
  "FLAMINKNO",  // #973: Flaminkno
  "FLANIWAL",  // #974: Flaniwal
  "KOLOWAL",  // #975: Kolowal
  "AGILUZA",  // #976: Agiluza
  "HEERASHAI",  // #977: Heerashai
  "NIGIRAGI",  // #978: Nigiragi
  "EPITAFF",  // #979: Epitaff
  "SUELORD",  // #980: Suelord
  "FARIGIRAF",  // #981: Farigiraf
  "DUMMIMISEL",  // #982: Dummimisel
  "GLADIMPERIO",  // #983: Gladimperio
  "RIESENZAHN",  // #984: Riesenzahn
  "BRUELLSCHWEIF",  // #985: Brüllschweif
  "WUTPILZ",  // #986: Wutpilz
  "FLATTERHAAR",  // #987: Flatterhaar
  "KRIECHFLUEGEL",  // #988: Kriechflügel
  "SANDFELL",  // #989: Sandfell
  "EISENRAD",  // #990: Eisenrad
  "EISENBUENDEL",  // #991: Eisenbündel
  "EISENHAND",  // #992: Eisenhand
  "EISENHALS",  // #993: Eisenhals
  "EISENFALTER",  // #994: Eisenfalter
  "EISENDORN",  // #995: Eisendorn
  "FROSPINO",  // #996: Frospino
  "CRYOSPINO",  // #997: Cryospino
  "ESPINODON",  // #998: Espinodon
  "GIERSPENST",  // #999: Gierspenst
  "MONETIGO",  // #1000: Monetigo
  "CHONGJIAN",  // #1001: Chongjian
  "BAOJIAN",  // #1002: Baojian
  "DINGLU",  // #1003: Dinglu
  "YUYU",  // #1004: Yuyu
  "DONNERSICHEL",  // #1005: Donnersichel
  "EISENKRIEGER",  // #1006: Eisenkrieger
  "KORAIDON",  // #1007: Koraidon
  "MIRAIDON",  // #1008: Miraidon
  "WINDEWOGE",  // #1009: Windewoge
  "EISENBLATT",  // #1010: Eisenblatt
  "SIRAPFEL",  // #1011: Sirapfel
  "MORTCHA",  // #1012: Mortcha
  "FATALITCHA",  // #1013: Fatalitcha
  "BONINU",  // #1014: Boninu
  "BENESARU",  // #1015: Benesaru
  "BEATORI",  // #1016: Beatori
  "OGERPON",  // #1017: Ogerpon
  "BRIDURADON",  // #1018: Briduradon
  "HYDRAPFEL",  // #1019: Hydrapfel
  "KEILFLAMME",  // #1020: Keilflamme
  "FURIENBLITZ",  // #1021: Furienblitz
  "EISENFELS",  // #1022: Eisenfels
  "EISENHAUPT",  // #1023: Eisenhaupt
  "TERAPAGOS",  // #1024: Terapagos
  "INFAMOMO",  // #1025: Infamomo
};
static_assert(sizeof(POKEMON_NAMES_DE) / sizeof(POKEMON_NAMES_DE[0]) == DEX_COUNT + 1,
              "German names must match the full National Dex");

const char *pokemonName(uint16_t dex) {
  if (dex == 0 || dex > DEX_COUNT) return "?";
  return gLang == LANG_DE ? POKEMON_NAMES_DE[dex] : DEX_TBL[dex].name;
}

const char *moveName(uint8_t move) {
  if (move >= MOVE_COUNT) move = MV_NONE;
  return MOVE_NAME_TBL[gLang][move];
}

const char *T(StrId id) { return STRINGS[gLang][id]; }
const char *medalName(int i)  { return MED_NAME[gLang][i]; }
const char *medalLabel(int i) { return MED_LBL[gLang][i]; }
const char *medalDesc(int i)  { return MED_DSC[gLang][i]; }

void loadLang() {
  Preferences p;
  p.begin("tamapoke", true);  // solo lectura
  uint8_t v = p.getUChar("lang", LANG_DEFAULT);
  p.end();
  gLang = (v < LANG_COUNT) ? (Lang)v : LANG_DEFAULT;
}

void setLang(Lang l) {
  if (l >= LANG_COUNT) return;
  gLang = l;
  Preferences p;
  p.begin("tamapoke", false);
  if (!p.putUChar("lang", (uint8_t)l)) logKeyFailure("i18n", "lang");
  p.end();
}
