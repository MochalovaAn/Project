//ЗДЕСЬ ИСПОЛЬЗУЕТСЯ C#!!!


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
 
namespace Arifm_coding
{
    /*class Program
    {
        static void Main(string[] args)
        {
            string word = "PROGRAM";
            
            ArifmCode code = new ArifmCode();
 
            code.Build(word);
            List<Node> nodes = code.GetSymbolsRanges(word);
            List<Node> allCodedNodes = code.Encode(word);
            string decodedNodes = code.Decode(allCodedNodes, word.Length);
 
            Console.ForegroundColor = ConsoleColor.Magenta;
            Console.WriteLine("\n  КОДИРУЕМОЕ СЛОВО:   " + word + "\n");
            Console.WriteLine("\n  Символ  |   Границы символa  | Частота появления");
            Console.WriteLine("----------------------------------------------------");
            foreach (Node node in nodes)
            {
                Console.Write("{0,5}:    |", node.Symbol);
                Console.Write("{0,8:f1}  -", node.Low);
                Console.Write("{0,5:f1}    |", node.High);
                Console.WriteLine("{0,8}", node.Frequency);
            }
            Console.WriteLine("----------------------------------------------------");
            
            Console.WriteLine("\n\n\n\n    НОВЫЕ ГРАНИЦЫ ДЛЯ СИМВОЛОВ: \n");
            Console.WriteLine("\n  Символ  |   Границы символa");
            Console.WriteLine("----------------------------------------------------");
            foreach (Node codedNode in allCodedNodes)
            {
                Console.Write("{0,5}:    |", codedNode.Symbol);
                Console.Write("{0,12}   -", codedNode.Low);
                Console.WriteLine("{0,12}", codedNode.High);
            }
            Console.WriteLine("----------------------------------------------------");
            Console.WriteLine("\n");
 
            Console.WriteLine("  ДЕКОДИРОВАНИЕ:   " + decodedNodes);
            Console.ReadLine();
        }       
    }*/
 
public class Node
    {
        public char Symbol { get; set; }
        public double Low { get; set; }
        public double High { get; set; }
        public double Range { get; set; }
        public int Frequency { get; set; }
    }
 
public class ArifmCode
    {
        private List<Node> nodes = new List<Node>();
        public Dictionary<char, int> Frequencies = new Dictionary<char, int>();
 
        public void Build(string source)
        {
            for (int i = 0; i < source.Length; i++)
            {
                if (!Frequencies.ContainsKey(source[i]))
                {
                    Frequencies.Add(source[i], 0);
                }
 
                Frequencies[source[i]]++;
            }
 
            foreach (KeyValuePair<char, int> symbol in Frequencies)
            {
                nodes.Add(new Node() { Symbol = symbol.Key, Frequency = symbol.Value });
            }
 
            nodes = nodes.OrderBy(node => node.Frequency).ToList<Node>();
        }
 
        public List<Node> GetSymbolsRanges(string source)
        {
            double low = 0;
            foreach (Node node in nodes)
            {
                node.Range = Math.Round(((double)(node.Frequency) / (source.Length)), 1);
                node.Low = Math.Round(low, 1);
                node.High = low + node.Range;
                low += node.Range;
            }
            return nodes;
        }
 
        public List<Node> Encode(string source)
        {
            nodes.Reverse();
            List<Node> allNodes = new List<Node>();
            
            for (int i = 0; i < source.Length; i++)
            {
                for (int j = 0; j < nodes.Count; j++)
                {
                    if (source[i] == nodes[j].Symbol)
                    {
                        allNodes.Add(new Node() { Symbol = nodes[j].Symbol, Low = nodes[j].Low, High = nodes[j].High });
                    }
                }
            }
 
            for (int i = 1; i < allNodes.Count; i++)
            {
                for (int j = 0; j < nodes.Count; j++)
                {
                    if (allNodes[i].Symbol == nodes[j].Symbol)
                    {
                        allNodes[i].High = allNodes[i - 1].Low + (allNodes[i - 1].High - allNodes[i - 1].Low) * nodes[j].High;
                        allNodes[i].Low = allNodes[i - 1].Low + (allNodes[i - 1].High - allNodes[i - 1].Low) * nodes[j].Low;
                    }
                }
            }
            return allNodes;
        }
 
        public string Decode(List<Node> allNodes, int count)
        {
            string decode = "";
            double code = allNodes[allNodes.Count - 1].Low;
            int symbolsCount = 0;
 
            while (true)
            {
                for (int i = 0; i < nodes.Count; i++)
                {
                    if (code >= nodes[i].Low && code < nodes[i].High)
                    {
                        decode += nodes[i].Symbol;
                        code = Math.Round((code - nodes[i].Low) / (nodes[i].High - nodes[i].Low), 8);
 
                        symbolsCount++;
                        if (symbolsCount == count)
                            return decode;
                    }
                }
            }
        }
    }
 
 
}