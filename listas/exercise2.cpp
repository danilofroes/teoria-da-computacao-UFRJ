/**
 * @brief Exercício 2:
 *        Calcule o número de Gödel associado à expressão P₂(x₁) → α₁
 * 
 * @author Danilo Fróes
 * @date 2026-03-19
 */

#include <iostream>
#include <map>
#include <string>
#include <cstdint>
#include <array>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>

size_t calculaVariavelGodel(const std::u32string &variavel);

/// @brief Primos maiores que 13 para a aritmetização de Gödel (limitado a 5 para um exercício simples)
std::array<uint8_t, 5> primosMaior13 = {17, 19, 23, 29, 31};

/// @brief Primos para cálculo de Gödel (limitado a 15)
std::array<uint8_t, 15> primos = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

/// @brief Mapeamento da aritmetização de Gödel com leves modificações do Nagel and Newman. Tabela do livro Teoria da Computação, de Flávio Mello.
std::map<const std::u32string, size_t> aritmetizacaoGodel = {
    {U"\u00AC", 3}, // negação (¬)
    {U"\u2192", 3}, // se-então (→)
    {U"\u2203", 3}, // existe (∃)
    {U"0", 7},      // zero
    {U"suc", 9},    // função sucessor
    {U"(", 11},     // abre parêntese - separador
    {U")", 13},     // fecha parêntese - separador

    // Variáveis x
    {U"x\u2081", calculaVariavelGodel(U"x\u2081")}, {U"x\u2082", calculaVariavelGodel(U"x\u2082")}, {U"x\u2083", calculaVariavelGodel(U"x\u2083")}, {U"x\u2084", calculaVariavelGodel(U"x\u2084")}, {U"x\u2085", calculaVariavelGodel(U"x\u2085")},
    
    // Números alpha
    {U"\u03B1\u2081", calculaVariavelGodel(U"\u03B1\u2081")}, {U"\u03B1\u2082", calculaVariavelGodel(U"\u03B1\u2082")}, {U"\u03B1\u2083", calculaVariavelGodel(U"\u03B1\u2083")}, {U"\u03B1\u2084", calculaVariavelGodel(U"\u03B1\u2084")}, {U"\u03B1\u2085", calculaVariavelGodel(U"\u03B1\u2085")},

    // Predicados P
    {U"P\u2081", calculaVariavelGodel(U"P\u2081")}, {U"P\u2082", calculaVariavelGodel(U"P\u2082")}, {U"P\u2083", calculaVariavelGodel(U"P\u2083")}, {U"P\u2084", calculaVariavelGodel(U"P\u2084")}, {U"P\u2085", calculaVariavelGodel(U"P\u2085")}
};

size_t calculaVariavelGodel(const std::u32string &variavel) {
    char32_t indice = variavel[1]; // Extrai o índice da variável (x₁, x₂, ...)
    uint8_t primo = 0;

    switch (indice) {
        case U'\u2081': primo = primosMaior13[0]; break; // x₁
        case U'\u2082': primo = primosMaior13[1]; break; // x₂
        case U'\u2083': primo = primosMaior13[2]; break; // x₃
        case U'\u2084': primo = primosMaior13[3]; break; // x₄
        case U'\u2085': primo = primosMaior13[4]; break; // x₅
    }

    if (variavel[0] == U'x') return primo;                      // (caso x - variáveis) primo elevado a 1
    else if (variavel[0] == U'\u03B1') return primo * primo;    // (caso alpha - números) primo elevado a 2
    else if (variavel[0] == U'P') return primo * primo * primo; // (caso P - predicados) primo elevado a 3
    else return 0;                                              // Caso inválido
}

int main() {
    // Expressão a ser calculada: P₂(x₁) → α₁
    std::u32string expressao = U"P\u2082(x\u2081)\u2192\u03B1\u2081";

    // Variável para armazenar o número de Gödel calculado
    boost::multiprecision::cpp_int numeroGodel = 1;
    
    for (uint8_t i = 0; i < expressao.size(); i++) {
        uint8_t j = 0; // Índice para os primos (não da para usar o i por causa dos símbolos de 2 caracteres)
        char32_t simbolo = expressao[i];
        size_t valorSimbolo = 0;

        // Variáveis, números e predicados são tratados como um símbolo único (ex: x₁, α₁, P₂)
        if (simbolo == U'x' || simbolo == U'\u03B1' || simbolo == U'P') {
            std::u32string simboloCompleto = {expressao[i], expressao[i + 1]}; // Combina o símbolo com seu índice (ex: x + ₁ = x₁)
            valorSimbolo = aritmetizacaoGodel[simboloCompleto];
            i++;
        }

        else {
            std::u32string simboloSimples(1, expressao[i]);
            valorSimbolo = aritmetizacaoGodel[simboloSimples];
        }

        numeroGodel *= boost::multiprecision::pow(boost::multiprecision::cpp_int(primos[j]), valorSimbolo);
        j++;
    }

    std::cout << "O número de Gödel associado à expressão P₂(x₁) → α₁ é: " << numeroGodel << std::endl;
    
    return 0;
}

/**
 * @result Após executar o código, o número de Gödel associado à expressão P₂(x₁) → α₁ é:
 * 
 * 1017955551923815835444390117360717618638982250262871787986052217276421042296357305664490
 * 5780832493415441566183320269815908262053552764778352330409073449646732147422149004920687
 * 1593945089297887988431513724662743088935905147267269190272454091076031961160639377642128
 * 6731693800768705321911354034558134796759104454457523689909179652208791449999864339981227
 * 0226132934589586561764496820601091654369835551214534452808111593262053856747751986697752
 * 2899643482579915839734189527240056548631883456088410618368077103741584170968727889166784
 * 3852927200241044322690860291782446488703336882373599297880261407437075908895111621223961
 * 6363952381688068735542733119453762994529299041915089864768064391232982968236216546854112
 * 4786892783923692873912233034530573289223389587686049221915416802833318983755819757198075
 * 8255984160751038927710339063977579163288014063168726751220468196384113389773352922357358
 * 5279659383172464502565645689039034637787027380439252510612838940681207272457769434148376
 * 0583613194651631837416708761868149801408326293572939568449857388835251592676130319911200
 * 0102458517659424642090753137360907033579103314028764921310655559491269312172974101909776
 * 9647500693629300634681153800094753287404619010559420190241069933652670893566774067125361
 * 7491899077700129971496914727109918713262546299770923090973000301107357841172589343095944
 * 3262403379496527591570551963811091665603173596580762500238743767174398338241723612296294
 * 8292182061912316457635537020419046040850214101420797616850787851707687948296316575783134
 * 5502761830462904245044574921260222755737901258348766065438967757696415620518751035537574
 * 3350584253316844203073245874645211833828226109344293395578580167211396705985759925092123
 * 4539692188022762902344377003501138278907437875794404249340442801701588078292532106107899
 * 6449628296075445897851828125501731935553787954667759806183942070478887177309577372287750
 * 7812125447803929898573518986070351237140616692508714132712007868426497332981420482288125
 * 4946158664505555793648705967538600473360119383760372488806214318269899288381311073446766
 * 0772832694590223843857999545351830208325605858282089516805224835287285664016745986549149
 * 258697806552302556121750085658859275611760911655632896
 * 
 * Por maior que o número seja, ele é finito e representa a expressão P₂(x₁) → α₁ de acordo com a aritmetização de Gödel,
 * além do tempo de execução ter sido praticamente instantâneo.
 */