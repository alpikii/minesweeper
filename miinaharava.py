import haravasto
import random
import time

tila = {
    "miinat": 0,
    "kentta" : [],
    "kentta_nakyma" : [],
    "liput" : 0,
    "jaljella" : [],
    "aloitus_aika" : 0,
    "klikkaukset" : 0
}

def avaa_ruutu(x, y):
    tarkista_havio(x, y)
    if tila["kentta"][y][x] == "0": #tarkistaa pitääkö tulvatäyttöä tehdä
        tulvataytto(x, y)
        tarkista_voitto()
    else:
        tila["kentta_nakyma"][y][x] = tila["kentta"][y][x] #avaa ruutuun näkymään viereisten miinojen lukumäärän
        tarkista_voitto()
       
def tarkista_havio(x, y):
    if tila["kentta"][y][x] == "x": #tarkistetaan onko ruudussa miina
        aika = lopeta_ajastin()
        tallenna_tiedot(False, aika)
        haravasto.lopeta() #jos ruudussa on miina peli päättyy
        print("Hävisit hahahaha >:). Aikaa kului {aika:.2f}".format(aika=aika))

def tarkista_voitto():
    voitto = 1
    if tila["miinat"] >= tila["liput"]: #tarkistaa ettei koko kenttää ole vaan tuikattu täyteen lippuja
        for rivi,lista in enumerate(tila["kentta"]):
            for sarake,merkki in enumerate(lista):
                if merkki != "x":
                    if tila["kentta_nakyma"][rivi][sarake] == tila["kentta"][rivi][sarake]: #katsoo että kaikki ruudut paitsi miinoja sisältävät ovat avattu
                        continue
                    else:
                        voitto = 0
        if voitto == 1:
            aika = lopeta_ajastin()
            tallenna_tiedot(True, aika)
            haravasto.lopeta()
            print("VOITIT :). Peliin kului aikaa {:.2f} sekuntia".format(aika))
                

def laita_lippu(x, y):
    if tila["kentta_nakyma"][y][x] == "f":
        tila["kentta_nakyma"][y][x] = " "
        tila["liput"] -= 1
        tarkista_voitto()
        
    else:
        tila["kentta_nakyma"][y][x] = "f"
        tila["liput"] += 1
        tarkista_voitto()

def aloita_ajastin():
    aloitusaika = time.time()
    return aloitusaika
    
def lopeta_ajastin():
    lopetusaika = time.time()
    peli_aika = lopetusaika - tila["aloitus_aika"]
    return peli_aika

def miinoita(kentta, vapaat, miinalkm):
    valitut_pisteet = random.sample(vapaat, miinalkm)
    for x, y in valitut_pisteet: 
        kentta[y][x] = "x"
    tila["miinat"] = miinalkm

def numeroi():
    for y, rivi in enumerate(tila["kentta"]):
        for x, merkki in enumerate(rivi):
            if merkki != "x":
                maara = 0
                for i in ((y-1, x-1), (y-1, x), (y-1, x+1), (y, x-1), (y, x+1), (y+1, x-1), (y+1, x), (y+1, x+1)):     
                    yi = i[0]
                    xi = i[1]
                    if yi < 0 or xi < 0 or yi > (len(tila["kentta"]) -1) or xi > (len(tila["kentta"][0]) - 1):
                        continue
                    else:
                        if tila["kentta"][yi][xi] == "x":
                            maara += 1
                tila["kentta"][y][x] = str(maara)
   
def tee_kentta():
    kentta = []
    kentta_nakyma = []
    jaljella = []
    leveys, korkeus = pyyda_dimensiot()
    for rivi in range(korkeus):
        kentta.append([])
        kentta_nakyma.append([])
        for sarake in range(leveys):
            kentta[rivi].append(" ")
            kentta_nakyma[rivi].append(" ")
    tila["kentta"] = kentta
    tila["kentta_nakyma"] = kentta_nakyma
    for x in range(leveys):
        for y in range(korkeus):
            jaljella.append((x, y))
    tila["jaljella"] = jaljella
    miinalkm = pyyda_miinat(leveys, korkeus)
    miinoita(tila["kentta"],tila["jaljella"], miinalkm)

def piirra_kentta():
    haravasto.tyhjaa_ikkuna()
    haravasto.piirra_tausta()
    haravasto.aloita_ruutujen_piirto()
    for yi, rivi in enumerate(tila["kentta_nakyma"]):
        for xi, ruutu in enumerate(rivi):
            haravasto.lisaa_piirrettava_ruutu(ruutu, 40*xi, 40*yi)
    haravasto.piirra_ruudut()

def kasittele_hiiri(x, y, painike, nappaimet):
    painikkeet = {
    haravasto.HIIRI_VASEN : "vasen",
    haravasto.HIIRI_KESKI : "keski",
    haravasto.HIIRI_OIKEA : "oikea"
    }
    x_koord = int(x/40)
    y_koord = int(y/40)
    if painike == haravasto.HIIRI_VASEN:
        tila["klikkaukset"] += 1
        avaa_ruutu(x_koord, y_koord)
    elif painike == haravasto.HIIRI_OIKEA:
        laita_lippu(x_koord, y_koord)
 
def tulvataytto(x, y):
    tyo = [(x, y)]
    valmiit = []
    naapurit = []
    if tila["kentta"][y][x] == "x":
        pass
    else:
        while tyo:
            x1, y1 = tyo.pop()
            tila["kentta"][y1][x1] = "0"
            tila["kentta_nakyma"][y1][x1] = tila["kentta"][y1][x1]
            valmiit.append((x1, y1))
            for i in ((y1-1, x1-1), (y1-1, x1), (y1-1, x1+1), (y1, x1-1), (y1, x1+1), (y1+1, x1-1), (y1+1, x1), (y1+1, x1+1)):
                yi = i[0]
                xi = i[1]
                if yi < 0 or xi < 0 or yi > len(tila["kentta"]) -1 or xi > len(tila["kentta"][0]) - 1:
                    continue
                else: 
                    naapurit.append((xi, yi))
                for naapuri in naapurit:
                    x_koordinaatti, y_koordinaatti = naapurit.pop()
                    if tila["kentta"][y_koordinaatti][x_koordinaatti] == "x":
                        pass
                    elif (x_koordinaatti, y_koordinaatti) in valmiit:
                        pass
                    else:
                        if tila["kentta"][y_koordinaatti][x_koordinaatti] == "0":
                            if (x_koordinaatti, y_koordinaatti) not in tyo:
                                tyo.append((x_koordinaatti, y_koordinaatti))
                                tila["kentta_nakyma"][y_koordinaatti][x_koordinaatti] = "0"
                        if tila["kentta"][y_koordinaatti][x_koordinaatti] != "0":
                            tila["kentta_nakyma"][y_koordinaatti][x_koordinaatti] = tila["kentta"][y_koordinaatti][x_koordinaatti]

def pyyda_dimensiot():
    while True:
        try:
            leveys = int(input("Anna kentän leveys: "))
            korkeus = int(input("Anna kentän korkeus: "))
        except ValueError:
            print("Vastauksen tulee olla kokonaisluku.")
        else:
            if leveys <= 0 or korkeus <= 0:
                print("Anna kentälle vähän enemmän dimensioita.")
            else:
                return leveys, korkeus

def pyyda_miinat(leveys, korkeus):
    while True:
        try:
            miinalkm = int(input("Anna miinojen lukumäärä: "))
        except ValueError:
            print("Vastauksen tulee olla kokonaisluku.")
        else:
            if miinalkm <= 0:
                print("Älä huijaa :( anna miinoja")
            elif miinalkm > leveys * korkeus:
                print("Nyt tuli iikaa miinoja")
            else:
                return miinalkm

def tallenna_tiedot(lopputulos, aika):
    paivays = time.strftime("%d:%m:%Y")
    kellonaika = time.strftime("%H:%M")
    korkeus = len(tila["kentta"])
    leveys = len(tila["kentta"][0])
    min = aika // 60
    s = aika % 60
    if lopputulos == True:
        tulos = "Voitto "
    else:
        tulos = "Häviö "
    try:
        with open("miinaharava_tulokset.txt", "a") as tulokset:
            tulokset.write("{tulos} {paiva} kello {klo} kentällä {l}x{k}, aikaa kului {min:.2f} min ja {s:.2f} s, vuoroja {klik} ja miinoja {miinat}\n".format(
                tulos=tulos,
                paiva=paivays,
                klo=kellonaika,
                min=min,
                s=s,
                klik=tila["klikkaukset"],
                miinat=tila["miinat"],
                k=korkeus,
                l=leveys
                ))
    except:
        print("Jotakin meni pieleen, peliä ei voitu tallentaa")

def main():
    tee_kentta()
    numeroi()
    haravasto.lataa_kuvat("spritet.zip\spritet")
    haravasto.luo_ikkuna(len(tila["kentta_nakyma"][0]) * 40, len(tila["kentta_nakyma"]) * 40)
    haravasto.aseta_piirto_kasittelija(piirra_kentta)
    haravasto.aseta_hiiri_kasittelija(kasittele_hiiri)
    tila["aloitus_aika"] = aloita_ajastin()
    haravasto.aloita()

def tulosta_tiedot():
    try:
        file = open("miinaharava_tulokset.txt", "r")
        for line in file.readlines():
            print(line)
    except FileNotFoundError:
        print("Tietoja ei ole\n")

def nollaa_arvot(): #varmistaa että kaikki arvot on nollattu seuraavaa peliä varten
    tila["aloitus_aika"] = 0
    tila["jaljella"] = []
    tila["kentta"] = []
    tila["kentta_nakyma"] = []
    tila["klikkaukset"] = 0
    tila["liput"] = 0
    tila["miinat"] = 0
                

if __name__ == "__main__":
    print("Tervetuloa pelaamaan miinaharavaa!")
    while True:
        print("Valinnat:")
        print("p = uusi peli")
        print("t = tiedot")
        print("l = lopeta")
        valinta = input(":").lower()
        if valinta == "p":
            nollaa_arvot()
            main()
        elif valinta == "t":
            tulosta_tiedot()
        elif valinta == "l":
            exit()
        else:
            print("Valinnan tulee olla yksi annetuista vaihtoehdoista\n")
            continue
