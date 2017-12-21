% FUNCAO QUE RETORNA UM VETOR NUMA MATRIZ Mat 3D NOS INDICE (n,m) E PROFUNDIDADE dim 
function vetor = getDescritor(n, m, Mat, dim)
%inicializa vetor
vetor = zeros(1, dim);
%recebe vetor da matriz
for i = 1:dim
   vetor(i) = Mat(n, m, i);
end
