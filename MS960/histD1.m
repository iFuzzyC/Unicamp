% SCRIPT PRINCIPAL
% CALCULA O DESCRITOR DE CADA IMAGEM
% CLASSIFICA CADA IMAGEM DO CONJUNTO DE TESTE

%inicializando variaveis
tamanho = 128;
dimensao = tamanho*tamanho;
comprimento = 26;
img_pixels = zeros(tamanho + 2, tamanho + 2);
Imagens_descritores = zeros(10, 12, comprimento);
%recebendo a primeira imagem
nome = 'c001_001.png';

%CALCULANDO OS DESCRITORES
for class = 1:10
    %definindo a classe no nome
    if (class == 10)
        nome(3) = int2str(1);
        nome(4) = int2str(0);
    else
        nome(4) = int2str(class);
    end
    for num = 1:12
        %definindo o numero da imagem
        if (num >= 10)
            nome(7) = int2str(1);
            if (num == 10) nome(8) = int2str(0);
            elseif (num == 11) nome(8) = int2str(1);
            elseif (num == 12) nome(8) = int2str(2);
            end
        end
        if (num < 10)
            nome(7) = int2str(0);
            nome(8) = int2str(num);
        end
        %recebendo a imagem
        img = imread(nome);
        %colocando em escala de cinza
        img = rgb2gray(img);
        
        %criando a matriz extendida dos pixels
        for i = 2:(tamanho + 1)
            for j = 2:(tamanho + 1)
                img_pixels(i,j) = img(i-1,j-1);
            end
        end
        
        %criando o vetor descritor da imagem
        img_descritor = zeros(1, dimensao);
        %percorrendo os pixels da imagem
        for i = 2:(tamanho + 1)
            for j = 2:(tamanho + 1)
                %cria o vetor binario
                bin = zeros(1, 8);
                %recebe o valor do pixel central
                img_pcentral = img_pixels(i,j);
                %compara central com os 8 vizinhos
                if (img_pixels(i,j+1) < img_pcentral) bin(1) = 1; end
                if (img_pixels(i-1,j+1) < img_pcentral) bin(2) = 1; end
                if (img_pixels(i-1,j) < img_pcentral) bin(3) = 1; end
                if (img_pixels(i-1,j-1) < img_pcentral) bin(4) = 1; end
                if (img_pixels(i, j-1) < img_pcentral) bin(5) = 1; end
                if (img_pixels(i+1, j-1) < img_pcentral) bin(6) = 1; end
                if (img_pixels(i+1,j) < img_pcentral) bin(7) = 1; end
                if (img_pixels(i+1,j+1) < img_pcentral) bin(8) = 1; end
                %calcula a escala de cinza comparativa do pixel central
                escala_cinza = 0;
                for p = 1:8
                    escala_cinza = escala_cinza + bin(p)*power(2, p-1);
                end
                %atribui o valor ao vetor descritor
                img_descritor((i-2)*tamanho + j-1) = escala_cinza;
                
            end
        end
        %calcula o vetor de valores do histograma
        histograma = histcounts(img_descritor);
        %passa o vetor descritor para a matriz das imagens
        for k = 1:comprimento 
            Imagens_descritores(class, num, k) = histograma(k);
        end
        %limpa a variavel
        clear histograma;
    end 
end

%CLASSIFICANO AS IMAGENS
Imagens_class = zeros(10, 6);

for class = 1:10
    for num = 1:6
        %pego um descritor de teste
        v_teste = getDescritor(class, num+6, Imagens_descritores, comprimento);
        %pego primeiro descritor de treino
        v_treino = getDescritor(1, 1, Imagens_descritores, comprimento);
        %calcula distancia entre os dois
        dist = distDois(v_teste, v_treino, comprimento);
        %set a class como 1
        Imagens_class(class, num) = 1;
        %comparando com o resto dos vetores descritores de treino
        for i = 1:10
            for j = 1:6
                v_treino = getDescritor(i, j, Imagens_descritores, comprimento);
                comp_dist = distDois(v_teste, v_treino, comprimento);
                if (comp_dist <= dist)
                    Imagens_class(class, num) = i;
                    dist = comp_dist;
                end
            end
        end
    end
end

%CALCULANDO PORCENTAGEM DE ACERTO
total = 10*6;
acertos = 0;
for i = 1:10
    for j = 1:6
        if(Imagens_class(i,j) == i) 
            acertos = acertos + 1;
        end
    end
end

fprintf('A porcentagem de acerto foi de ');
acertos/total * 100

