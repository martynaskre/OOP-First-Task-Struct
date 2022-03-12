//
// Created by Martynas Skrebė on 2022-03-12.
//

#include <sstream>
#include <iostream>
#include <vector>
#include "Faker.h"


const std::vector<std::string> Faker::firstNames = { "Abramas", "Abraomas", "Achilas", "Adalbertas", "Adamas", "Adas", "Adolfas", "Adolis", "Adomas",
                                   "Adrijus", "Agatas", "Agnius", "Aidas", "Ainius", "Aistis", "Aivaras", "Akimas", "Akvilinas", "Albertas", "Albrechtas",
                                   "Albinas", "Aldonas", "Aleksandras", "Aleksas", "Alenas", "Alfas", "Alfonsas", "Alfredas", "Algimantas", "Algirdas",
                                   "Algis", "Alius", "Almantas", "Almis", "Almonas", "Aloyzas", "Alpas", "Alpis", "Alvidas", "Alvydas", "Ambraziejus",
                                   "Anatolijus", "Anatolis", "Andreas", "Andriejus", "Andrius", "Andžejus", "Anicetas", "Anisimas", "Antanas", "Antonas",
                                   "Antonijus", "Antonis", "Anupras", "Anzelmas", "Apolinaras", "Apolonijus", "Aras", "Arijus", "Arimantas", "Aristarchas",
                                   "Aristidas", "Arkadijus", "Armantas", "Arminas", "Arnas", "Arnoldas", "Aronas", "Arsenas", "Arsenijus", "Artas",
                                   "Artiomas", "Artūras", "Arūnas", "Arvaidas", "Arvydas", "Astijus", "Audrius", "Audrys", "Audronius", "Augis",
                                   "Augustas", "Augustinas", "Aurelijus", "Aurimas", "Aušrius", "Aušrys", "Ąžuolas", "Balys", "Baltazaras", "Baltramiejus",
                                   "Baltrus", "Banguolis", "Bartas", "Bartvydas", "Bazilijus", "Benas", "Benediktas", "Benonas", "Benius", "Benjaminas",
                                   "Bernardas", "Beržas", "Bijūnas", "Bogdanas", "Boguslavas", "Boleslavas", "Boleslovas", "Bonifacas", "Borisas",
                                   "Bronislavas", "Bronislovas", "Bronius", "Brunas", "Brunonas", "Cecilijus", "Celestinas", "Cezaris", "Chaimas",
                                   "Charitonas", "Ciprijonas", "Česius", "Česlovas", "Čiogintas", "Dainius", "Daivis", "Dalius", "Damijonas", "Danas",
                                   "Dangerutis", "Danielius", "Danila", "Danius", "Darijus", "Darius", "Dariušas", "Daumantas", "Davidas", "Deimantas",
                                   "Deividas", "Deivis", "Demetrijus", "Demjanas", "Denis", "Denisas", "Dimitrijus", "Diomidas", "Dionizas", "Dmitrijus",
                                   "Dobilas", "Donatas", "Domantas", "Domas", "Dominykas", "Donaldas", "Dovydas", "Dovilis", "Dovis", "Drąsius",
                                   "Drąsutis", "Džeraldas", "Džiraldas", "Džiugas", "Džonis", "Edgaras", "Edmundas", "Eduardas", "Edvardas", "Edvinas",
                                   "Egidijus", "Eidimantas", "Eidminas", "Eidvydas", "Eimantas", "Eimis", "Einius", "Eivydas", "Eldaras", "Eligijus",
                                   "Elijus", "Elmantas", "Emanuelis", "Emilis", "Emilijonas", "Emilijus", "Enrikas", "Erazmas", "Erdvilas", "Erichas",
                                   "Erikas", "Ernestas", "Ervinas", "Eugenijus", "Eugeniušas", "Evaldas", "Fabijus", "Faustas", "Fedoras", "Felicijonas",
                                   "Felicijus", "Feliksas", "Ferdinandas", "Filipas", "Fiodoras", "Foma", "Flavijus", "Florijonas", "Francas",
                                   "Francišekas", "Fredas", "Fridrikas", "Gabrielis", "Gabrielius", "Gailimantas", "Gailius", "Galmantas", "Gasparas",
                                   "Gaudenis", "Gaudrimas", "Gaudvydas", "Gavrila", "Gavrilas", "Gedas", "Gedgaudas", "Gediminas", "Gedmantas", "Gedmas",
                                   "Gedminas", "Gedvaldas", "Gedvydas", "Gedvilas", "Geivydas", "Genadijus", "Gendrius", "Genrichas", "Georgijus",
                                   "Geraldas", "Gerardas", "Gerdas", "Gerimantas", "Germanas", "Germantas", "Gerutis", "Gervydas", "Giedrius", "Gilbertas",
                                   "Gintaras", "Gintas", "Gintis", "Gintautas", "Girėnas", "Girius", "Girmantas", "Girvydas", "Gitanas", "Gytautas",
                                   "Gytis", "Gordejus", "Gotfridas", "Gracijonas", "Gracijus", "Gražvydas", "Grigalius", "Grigas", "Grigorijus", "Gunaras",
                                   "Gustas", "Gustavas", "Gustis", "Gvidas", "Gvidonas", "Haraldas", "Haris", "Haroldas", "Hektoras", "Helmutas",
                                   "Henrikas", "Henris", "Herbertas", "Herkus", "Hermanas", "Hilarijus", "Horacijus", "Horstas", "Hubertas", "Ignacas",
                                   "Ignas", "Ignotas", "Igoris", "Ilja", "Imantas", "Indrius", "Ingvaras", "Inocentas", "Ipolitas", "Irenijus", "Irmantas",
                                   "Irtautas", "Irvydas", "Isaakas", "Isakas", "Ivanas", "Izidorius", "Izoldas", "Jacekas", "Jakovas", "Jakubas", "Janas",
                                   "Janis", "Jankelis", "Janušas", "Jaroslavas", "Jaunius", "Jaunutis", "Jegoras", "Jemeljanas", "Jeronimas", "Jevgenijus",
                                   "Ježis", "Joanas", "Jogaila", "Jogintas", "Jogirdas", "Jokimas", "Jokūbas", "Jolantas", "Jomantas", "Jonaras", "Jonas",
                                   "Jonis", "Joris", "Jorūnas", "Josifas", "Jotautas", "Jovaldas", "Jovaras", "Jovitas", "Judrius", "Julijonas", "Julijus",
                                   "Julius", "Juljanas", "Juozapas", "Juozapatas", "Juozas", "Juras", "Jurgis", "Jurijus", "Jūras", "Jūris", "Justas",
                                   "Justinas", "Juvencijus", "Juzefas", "Kajetonas", "Kajus", "Kalikstas", "Kalnius", "Kamilis", "Kaributas", "Karlas",
                                   "Karolis", "Karpas", "Kasparas", "Kastantas", "Kastytis", "Kazimieras", "Kazys", "Kęstas", "Kęstautas", "Kęstutis",
                                   "Kimas", "Kipras", "Kiprijonas", "Kirilas", "Klaudas", "Klaudijus", "Klemas", "Klemensas", "Klementas", "Kleopas",
                                   "Klevas", "Klimas", "Klimentijus", "Kondratas", "Konradas", "Konstantinas", "Kornelijus", "Kostas", "Kovas", "Kozmas",
                                   "Krescencijus", "Kristijonas", "Kristinas", "Kristoforas", "Kristupas", "Ksaveras", "Kšištofas", "Kuprijanas", "Laimis",
                                   "Laimonas", "Laimutis", "Laisvydas", "Laisvis", "Laisvūnas", "Lauras", "Laurentijus", "Laurynas", "Lauris",
                                   "Lavrentijus", "Leandras", "Leonardas", "Leonas", "Leonidas", "Leopoldas", "Levas", "Libertas", "Linas", "Lionginas",
                                   "Liubartas", "Liubomiras", "Liucijonas", "Liucijus", "Liudas", "Liudvigas", "Liudvikas", "Liūtas", "Liutauras",
                                   "Livijus", "Lozorius", "Lukas", "Lukrecijus", "Makaras", "Makarijus", "Maksas", "Maksimas", "Maksimilijonas",
                                   "Mamertas", "Manfredas", "Mangirdas", "Mantas", "Mantautas", "Mantrimas", "Mantvydas", "Maratas", "Marcelijus ",
                                   "Marcelinas", "Marcelius", "Marekas", "Margiris", "Marianas", "Marijonas", "Marijus", "Marinas", "Marius", "Markas",
                                   "Martas", "Martinas", "Martynas", "Matas", "Mateušas", "Matvejus", "Mažvydas", "Mečislavas", "Mečislovas", "Mečys",
                                   "Medardas", "Medas", "Mefodijus", "Melanijus", "Melchioras", "Mendelis", "Merkys", "Merūnas", "Michalas", "Michailas",
                                   "Miglius", "Mikalojus", "Mikas", "Mikolajus", "Milanas", "Mildas", "Milvydas", "Mindaugas", "Minijus", "Mykolas",
                                   "Mingaudas", "Mintaras", "Miroslavas", "Modestas", "Morkus", "Motiejus", "Mozė", "Naglis", "Napalis", "Napalys",
                                   "Napoleonas", "Napolis", "Narcizas", "Narimantas", "Narsutis", "Narvydas", "Natanas", "Natas", "Naumas", "Nauris",
                                   "Nazaras", "Nazarijus", "Nedas", "Neimantas", "Neivydas", "Nemunas", "Nerijus", "Nerimantas", "Nerimas", "Neringas",
                                   "Nerius", "Nidas", "Nikandras", "Nikas", "Nikiforas", "Nikita", "Nikodemas", "Nikola", "Nikolajus", "Nilas", "Nojus",
                                   "Nomedas", "Norbertas", "Normanas", "Normantas", "Nortautas", "Norvydas", "Norvilas", "Oktavijus", "Olegas", "Orestas",
                                   "Orintas", "Oskaras", "Osmundas", "Osvaldas", "Otas", "Otilijus", "Otonas", "Ovidijus", "Palemonas", "Palmyras",
                                   "Patricijus", "Patrikas", "Paulis", "Paulius", "Petras", "Pijus", "Pilypas", "Pilėnas", "Piotras", "Platonas",
                                   "Polikarpas", "Polis", "Povilas", "Pranas", "Pranciškus", "Putinas", "Radvila", "Rafaelis", "Rafailas", "Rafalas",
                                   "Raigardas", "Raimondas", "Raimundas", "Rainoldas", "Ralfas", "Ramintas", "Ramonas", "Ramūnas", "Rapolas", "Rasius",
                                   "Raulis", "Redas", "Regimantas", "Reginaldas", "Reinhardas", "Remas", "Remigijus", "Renaldas", "Renatas", "Renius",
                                   "Richardas", "Ričardas", "Rikardas", "Rimantas", "Rimas", "Rimgaudas", "Rimtas", "Rimtautas", "Rimtis", "Rimvydas",
                                   "Rinatas", "Ryšardas", "Rytas", "Rytautas", "Rytis", "Robertas", "Robinas", "Rodrigas", "Rokas", "Rolandas", "Rolfas",
                                   "Romanas", "Romas", "Romualdas", "Ronaldas", "Rostislavas", "Rubenas", "Rudolfas", "Rufas", "Rufinas", "Rupertas",
                                   "Ruslanas", "Rūtenis", "Sabinas", "Sakalas", "Saliamonas", "Salvijus", "Samuelis", "Samsonas", "Samuilas", "Sandras",
                                   "Santaras", "Saulenis", "Saulius", "Sava", "Sebastijonas", "Semas", "Semionas", "Serafinas", "Serapinas", "Sergejus",
                                   "Sergijus", "Seržas", "Severas", "Severinas", "Sidas", "Sidoras", "Sigis", "Sigitas", "Sigizmundas", "Sikstas",
                                   "Silverijus", "Silvestras", "Silvijus", "Simas", "Simeonas", "Simonas", "Sirvydas", "Skaidrius", "Skaistis",
                                   "Skalmantas", "Skalvis", "Skirgaila", "Skirmantas", "Skomantas", "Sonetas", "Stanislavas", "Stanislovas", "Stasys",
                                   "Stasius", "Stepas", "Stefanas", "Stepanas", "Steponas", "Svajūnas", "Svajus", "Sviatoslavas", "Šarūnas", "Šiaurys",
                                   "Švitrigaila", "Tadas", "Tadeušas", "Tamošius", "Tarasas", "Tauras", "Tautginas", "Tautrimas", "Tautvydas", "Tedas",
                                   "Telesforas", "Teisius", "Teisutis", "Teodoras", "Teofilis", "Terentijus", "Tiberijus", "Timas", "Timotiejus",
                                   "Timotis", "Timūras", "Titas", "Tomas", "Tomašas", "Tonis", "Traidenis", "Trofimas", "Tumas", "Ugnius", "Ulrikas",
                                   "Uosis", "Urbonas", "Utenis", "Ubaldas", "Ūdrys", "Ūkas", "Vacys", "Vacius", "Vaclovas", "Vadimas", "Vaidas",
                                   "Vaidevutis", "Vaidila", "Vaidis", "Vaidotas", "Vaidutis", "Vaigaudas", "Vaigirdas", "Vainius", "Vainoras", "Vaitiekus",
                                   "Vaižgantas", "Vakaris", "Valdas", "Valdemaras", "Valdimantas", "Valdis", "Valentas", "Valentinas", "Valerijonas",
                                   "Valerijus", "Valys", "Valius", "Valteris", "Vasaris", "Vasilijus", "Venantas", "Verneris", "Vėjas", "Vėjūnas",
                                   "Venjaminas", "Vergilijus", "Vestas", "Viačeslavas", "Vidas", "Vydas", "Vidimantas", "Vydimantas", "Vidmantas",
                                   "Vydmantas", "Viesulas", "Vygaudas", "Vigilijus", "Vygintas", "Vygirdas", "Vykantas", "Vykintas", "Viktas", "Viktoras",
                                   "Viktorijus", "Viktorinas", "Vilenas", "Vilgaudas", "Vilhelmas", "Vilijus", "Vilius", "Vylius", "Vilmantas", "Vilmas",
                                   "Vilnius", "Viltaras", "Viltautas", "Viltenis", "Vincas", "Vincentas", "Vingaudas", "Virgaudas", "Virgilijus",
                                   "Virginijus", "Virgintas", "Virgis", "Virgius", "Virmantas", "Vismantas", "Visvaldas", "Visvaldis", "Vitalijus",
                                   "Vitalis", "Vitalius", "Vitas", "Vitoldas", "Vygandas", "Vygantas", "Vykintas", "Vytaras", "Vytautas", "Vytas",
                                   "Vytenis", "Vytis", "Vyturys", "Vladas", "Vladimiras", "Vladislavas", "Vladislovas", "Vladlenas", "Voicechas",
                                   "Voldemaras", "Vsevolodas", "Zacharijus", "Zakarijus", "Zbignevas", "Zdislavas", "Zenius", "Zenonas", "Zigfridas",
                                   "Zygfridas", "Zigmantas", "Zigmas", "Zygmuntas", "Zinovijus", "Žanas", "Žeimantas", "Žilvinas", "Žibartas", "Žybartas",
                                   "Žydrius", "Žydrūnas", "Žygaudas", "Žygimantas", "Žygintas", "Žygis", "Žymantas", "Žvaigždžius" };

const std::vector<std::string> Faker::lastNames = { "Kazlaukas", "Jankauskas", "Petrauskas", "Stankevičius", "Vasiliauskas", "Žukauskas", "Butkus",
                                                    "Kateiva", "Paulauskas", "Urbonas", "Kavaliauskas", "Baranauskas", "Pocius", "Sakalauskas" };

std::random_device Faker::rd;

std::mt19937 Faker::mt(Faker::rd());

int Faker::randomNumber(int from, int to) {
    std::uniform_real_distribution<double> dist(from, to);

    return dist(Faker::mt);
}

std::string Faker::randomFirstName() {
    return Faker::firstNames[Faker::randomNumber(0, Faker::firstNames.size())];
}

std::string Faker::randomLastName() {
    return Faker::lastNames[Faker::randomNumber(0, Faker::lastNames.size())];
}

std::string Faker::randomFullName() {
    return Faker::randomFirstName() + " " + Faker::randomLastName();
}

int Faker::randomMark() {
    return Faker::randomNumber(0, 10);
}

