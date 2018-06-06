/* tag::bazaFaktow[] */
mezczyzna(franciszek).
mezczyzna(jan).
mezczyzna(bogdan).
mezczyzna(wojciech).
mezczyzna(krzysztof).
mezczyzna(wojciech).
mezczyzna(robert).
kobieta(wanda).
kobieta(maria).
kobieta(anna).
kobieta(zofia).
kobieta(ewa).
kobieta(katarzyna).
maz(X) :- mezczyzna(X).
zona(X) :- kobieta(X).
rodzic(franciszek, maria).
rodzic(wanda, bogdan).
rodzic(jan, krzysztof).
rodzic(maria, krzysztof).
rodzic(jan, wojciech).
rodzic(maria, wojciech).
rodzic(bogdan, ewa).
rodzic(anna, ewa).
rodzic(bogdan, zofia).
rodzic(anna, zofia).
rodzic(wojciech, katarzyna).
rodzic(zofia, katarzyna).
rodzic(wojciech, robert).
rodzic(zofia, robert).
ojciec(X, Y) :- rodzic(X, Y), mezczyzna(X).
matka(X, Y) :- rodzic(X, Y), kobieta(X).
malzenstwo(wojciech, zofia).
malzenstwo(jan, maria).
malzenstwo(bogdan, anna).
/* end::bazaFaktow[] */

/* tag::pokrewienstwo[] */
dziadek(X, Z) :- ojciec(X, Y), rodzic(Y, Z).
babcia(X, Z) :- matka(X, Y), rodzic(Y, Z).
syn(X, Y) :- rodzic(Y, X), mezczyzna(X).
corka(X, Y) :- rodzic(Y, X), kobieta(X).
brat(X, Z) :- ojciec(Y, X), ojciec(Y, Z), mezczyzna(X).
siostra(X, Z) :- ojciec(Y, X), ojciec(Y, Z), kobieta(X).
rodzenstwo(X, Y) :- rodzic(Z, X), rodzic(Z, Y), mezczyzna(Z).
przodek(X, Y) :- rodzic(X, Y).
przodek(X, Y) :- rodzic(X, Z), przodek(Z, Y).
potomek(X, Y) :- przodek(Y, X).
/* end::pokrewienstwo[] */

/* tag::pkt4[] */
ma_dzieci(X) :- potomek(_,X).
jest_dziadkiem(X) :- potomek(Y,X), potomek(_, Y), mezczyzna(X).
ciocia(X, Y) :- kobieta(X), rodzenstwo(X, Z), potomek(Y, Z).
wuj(X, Y) :- mezczyzna(X), rodzenstwo(X, Z), potomek(Y, Z).
/* end::pkt4[] */