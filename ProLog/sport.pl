jest(jan, pilkarz).
jest(marek, pilkarz).
jest(adam, plywak).
jest(jan, plywak).
jest(X, sportowiec) :- jest(X, plywak); biega(X).

biega(X) :- jest(X, pilkarz).

bierze_udzial_w_zawodach(X) :- jest(X, sportowiec), ma_kondycje(X).

ma_kondycje(X) :- jest(X, pilkarz). 