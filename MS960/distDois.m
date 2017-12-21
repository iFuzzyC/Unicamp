% FUNCAO QUE RETORNA A DISTANCIA EUCLIDIANA ENTRE DOIS VETORES DE TAMANHO dim
function dist = distDois(vetor1, vetor2, dim)
%inicializa distancia
dist = 0;
%devolve o quadrado da distancia
for i = 1:dim
   dist = dist + power(vetor1(i) - vetor2(i), 2); 
end
%devolve raiz quadrada da distancia
dist = power(dist, 0.5);