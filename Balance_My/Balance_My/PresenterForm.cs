using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace Balance_My
{
    public struct ForAnalys
    {
        public DateTime date;
        public int balance;
    }
    public class PresenterForm
    {
        private static List<BalanceBase> listBalance;
        private static List<BalanceBase> listCredit;
        private static List<BalanceBase> bufferMounth;

        /// <summary>
        /// буфер временной даты
        /// </summary>
        public static DateTime BufferDateTime { get; set; }

        /// <summary>
        /// список доходов только для чтения
        /// </summary>
        public static List<BalanceBase> ListBalance
        {
            get { return listBalance; }
        }
        /// <summary>
        /// список расходов только для чтения
        /// </summary>
        public static List<BalanceBase> ListCredit
        {
            get { return listCredit; }
        }
        /// <summary>
        /// добавить в список расход
        /// </summary>
        /// <param name="bb">тип баланса</param>
        public static void AddCredit(BalanceBase bb)
        {
            listCredit.Add(bb);
        }
        /// <summary>
        /// добавить в список доход
        /// </summary>
        /// <param name="bb">тип баланса</param>
        public static void AddBalance(BalanceBase bb)
        {
            listBalance.Add(bb);
            listBalance.Sort();          
        }

        /// <summary>
        /// удаление из базы
        /// </summary>
        /// <param name="index">Индекс масива</param>
        public static void removeBalance(int index)
        {
            listBalance.RemoveAt(index);
            //listBalance.Sort();
        }

        public static void removeCredit(int index)
        {
            listCredit.RemoveAt(index);
            //listBalance.Sort();
        }

        /// <summary>
        /// изменить обьект
        /// </summary>
        /// <param name="balance">Сам Объект</param>
        /// <param name="index">Индекс Базы Данных</param>
        public static void setBalance(BalanceBase balance, int index)
        {
            listBalance[index] = balance;
            //listBalance.Sort();
        }

        public static void setCredit(BalanceBase balance, int index)
        {
            listCredit[index] = balance;
            //listBalance.Sort();
        }

        /// <summary>
        /// добавить в буфер временных месячных данных дохода
        /// </summary>
        public static List<BalanceBase> BufferMounth
        {
            get { return bufferMounth; }
            set { bufferMounth = value; }       
        }

        /// <summary>
        /// добавить в буфер времменых месячных данных расхода
        /// </summary>
        public static List<BalanceBase> BufferMounthCredit { get; set; }       

        private void Initialize()
        {
            BinaryReader br = new BinaryReader(File.Open(Form1.DirSorce + "\\" + Form1.FileAccount + ".dat", FileMode.Open));

            try
            {
                Int32 count_category = br.ReadInt32();
                for (int i = 0; i < count_category; i++)
                {
                    Settings.category_list.Add(br.ReadString());
                }

                int cout = 0;
                int coutStop = br.ReadInt32();

                while (true)
                {
                    if (cout < coutStop)
                    {
                        string date = br.ReadString();
                        string category = br.ReadString();
                        int mony = br.ReadInt32();
                        string descr = br.ReadString();
                        BalanceBase bb = new BalanceBase(mony, date, category, descr);
                        listBalance.Add(bb);
                    }
                    else
                    {
                        int mony = br.ReadInt32();
                        string date = br.ReadString();
                        string descr = br.ReadString();
                        BalanceBase bb = new BalanceBase(mony, date, "", descr);
                        listCredit.Add(bb);
                    }
                    cout++;
                }
            }
            catch (EndOfStreamException ex)
            {
                //MessageBox.Show("Загрузка прошла успешно!", "загрузка", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }

            br.Close();
        }

        private void LoadBalance()
        {
            BinaryReader br = new BinaryReader(File.Open(Form1.DirSorce + "\\" + Form1.FileAccount + ".dat", FileMode.Open));

            Int32 count_category = br.ReadInt32();
            for (int i = 0; i < count_category; i++)
            {
                Settings.category_list.Add(br.ReadString());
            }

            //загружаю шаблон на описание расхода
            Int32 count_tamplate = br.ReadInt32();
            for (int i = 0; i < count_tamplate; i++)
            {
                Settings.tamplate_credit.Add(br.ReadString());
            }
            //-----------------------------------

            int countDebit = br.ReadInt32();
            int countCredit = br.ReadInt32();

            for (int i = 0; i < countDebit; i++)
            {
                string date = br.ReadString();
                string category = br.ReadString();
                int mony = br.ReadInt32();
                string descr = br.ReadString();
                BalanceBase bb = new BalanceBase(mony, date, category, descr);
                listBalance.Add(bb);
            }

            for (int i = 0; i < countCredit; i++)
            {
                int mony = br.ReadInt32();
                string date = br.ReadString();
                string descr = br.ReadString();
                BalanceBase bb = new BalanceBase(mony, date, "", descr);
                listCredit.Add(bb);
            }

            br.Close();
        }

        /// <summary>
        /// сохранить доходы и расходы
        /// </summary>
        internal static void SaveListBalance(string fileName)
        {
            BinaryWriter bw = new BinaryWriter(File.Open(fileName, FileMode.OpenOrCreate));

            bw.Write(Settings.category_list.Count);
            for (int i = 0; i < Settings.category_list.Count; i++)
            {
                bw.Write(Settings.category_list[i]);
            }

            //сохраняю шаблон на описание расхода (новое)
            bw.Write(Settings.tamplate_credit.Count);
            for (int i = 0; i < Settings.tamplate_credit.Count; i++)
            {
                bw.Write(Settings.tamplate_credit[i]);
            }
            //-------------------------------------------

            bw.Write(listBalance.Count);
            bw.Write(listCredit.Count);

            for (int i = 0; i < listBalance.Count; i++)
            {
                bw.Write(listBalance[i].DateBalance);
                bw.Write(listBalance[i].Category);
                bw.Write(listBalance[i].Money);
                bw.Write(listBalance[i].Description);
            }

            for (int j = 0; j < listCredit.Count; j++)
            {
                bw.Write(listCredit[j].Money);
                bw.Write(listCredit[j].DateBalance);
                bw.Write(listCredit[j].Description);
            }

            bw.Close();

            SaveListBalanceTXT(ListBalance, ListCredit);
        }

        private static bool SaveListBalanceTXT(List<BalanceBase> balance, List<BalanceBase> credit)
        {
            using (StreamWriter sw = new StreamWriter(Form1.DirSorce + "text\\" + Form1.FileAccount + ".txt"))
            {
                sw.WriteLine(Settings.category_list.Count);
                
                for (int i = 0; i < Settings.category_list.Count; i++)
                {
                    sw.WriteLine(Settings.category_list[i]);
                }

                sw.WriteLine(listBalance.Count);
                sw.WriteLine(ListCredit.Count);

                for (int i = 0; i < listBalance.Count; i++)
                {
                    sw.WriteLine(listBalance[i].DateBalance + "|" + listBalance[i].Category + "|" + listBalance[i].Money +
                        "|" + listBalance[i].Description);
                }

                for (int i = 0; i < listCredit.Count; i++)
                {
                    sw.WriteLine(listCredit[i].DateBalance + "|" + listCredit[i].Money + "|" + listCredit[i].Description);
                }
            }

            return true;
        }

        public static bool SaveListBalanceTXT(string fileName)
        {
            using (StreamWriter sw = new StreamWriter(fileName))
            {
                sw.WriteLine(Settings.category_list.Count);

                for (int i = 0; i < Settings.category_list.Count; i++)
                {
                    sw.WriteLine(Settings.category_list[i]);
                }

                sw.WriteLine(listBalance.Count);
                sw.WriteLine(ListCredit.Count);

                for (int i = 0; i < listBalance.Count; i++)
                {
                    sw.WriteLine(listBalance[i].DateBalance + "|" + listBalance[i].Category + "|" + listBalance[i].Money +
                        "|" + listBalance[i].Description);
                }

                for (int i = 0; i < listCredit.Count; i++)
                {
                    sw.WriteLine(listCredit[i].DateBalance + "|" + listCredit[i].Money + "|" + listCredit[i].Description);
                }
            }

            return true;
        }

        public PresenterForm()
        {
            listBalance = new List<BalanceBase>();
            listCredit = new List<BalanceBase>();
            bufferMounth = new List<BalanceBase>();
            BufferMounthCredit = new List<BalanceBase>();

            //Initialize();
            LoadBalance();
            LoadSumMounth();

            listBalance.Sort();
        }

        ~PresenterForm()
        {
            
        }
        /// <summary>
        /// сумма дохода за текущий месяц
        /// </summary>
        /// <returns>строка месяц сумма</returns>
        internal static string LoadSumMounth()
        {
            DateTime dt = DateTime.Now;

            int summa = 0;

            for (int i = 0; i < listBalance.Count; i++)
            {
                DateTime d = DateTime.Parse(listBalance[i].DateBalance);

                if (dt.Month == d.Month && d.Year == dt.Year)
                {
                    summa += listBalance[i].Money;
                }
            }

            return string.Format("сумма за ({0}) : {1} грн.", dt.ToString("y"), summa);
        }
        /// <summary>
        /// сумма дохода за все месяца
        /// </summary>
        /// <param name="list">сумма дохода за все месяца</param>
        /// <returns>масив строк месяцев</returns>
        internal static List<string> LoadSumMounth(List<BalanceBase> list)
        {
            DateTime dt = DateTime.Parse(list[0].DateBalance);

            List<string> mounth = new List<string>();

            int summa = 0;

            bool flag = false;

            for (int i = 0; i < list.Count; i++)
            {
                DateTime d = DateTime.Parse(list[i].DateBalance);

                if (dt.Month != d.Month || dt.Month == d.Month && dt.Year != d.Year)
                {
                    flag = true;
                }

                if (!flag)
                {
                    summa += list[i].Money;
                }
                else
                {
                    mounth.Add(String.Format("{0} итог : {1} грн.", dt.ToString("y"), summa));
                    summa = 0;
                    dt = d;
                    flag = false;
                    summa += list[i].Money;
                }

                if (list.Count -1 == i)
                    mounth.Add(String.Format("{0} итог : {1} грн.", dt.ToString("y"), summa));
            }

            if(mounth.Count == 0)
                mounth.Add(String.Format("{0} итог : {1} грн.", dt.ToString("y"), summa));

            return mounth;
        }

        internal static List<int> LoadSumMounthInt(List<BalanceBase> list)
        {
            DateTime dt = DateTime.Parse(list[0].DateBalance);

            List<int> mounth = new List<int>();

            int summa = 0;

            bool flag = false;

            for (int i = 0; i < list.Count; i++)
            {
                DateTime d = DateTime.Parse(list[i].DateBalance);

                if (dt.Month != d.Month || dt.Month == d.Month && dt.Year != d.Year)
                {
                    flag = true;
                }

                if (!flag)
                {
                    summa += list[i].Money;
                }
                else
                {
                    mounth.Add(summa);
                    summa = 0;
                    dt = d;
                    flag = false;
                    summa += list[i].Money;
                }

                if (list.Count - 1 == i)
                    mounth.Add(summa);
            }

            if (mounth.Count == 0)
                mounth.Add(summa);

            return mounth;
        }        

        public static List<ForAnalys> CounterSumMounth(List<BalanceBase> _balance)
        {
            List<ForAnalys> analys = new List<ForAnalys>();

            List<BalanceBase> tempBalance = new List<BalanceBase>(_balance);

            List<BalanceBase> mounthBalance = new List<BalanceBase>();

            while (tempBalance.Count > 0)
            {
                DateTime tempDate = DateTime.Parse(tempBalance[tempBalance.Count - 1].DateBalance);
                List<int> remove = new List<int>();

                for (int i = tempBalance.Count - 1; i >= 0; i--)
                {
                    BalanceBase bb = tempBalance[i];
                    DateTime locDate = DateTime.Parse(bb.DateBalance);

                    if((tempDate.Year == locDate.Year) && (tempDate.Month == locDate.Month))
                    {
                        mounthBalance.Add(bb);
                        remove.Add(i);
                    }
                }

                for (int i = 0; i < remove.Count; i++)
                    tempBalance.RemoveAt(remove[i]);

                ForAnalys result = new ForAnalys();
                result.date = DateTime.Parse(mounthBalance[0].DateBalance);
                for (int i = 0; i < mounthBalance.Count; i++)
                {
                    BalanceBase bb = mounthBalance[i];
                    result.balance += bb.Money;                    
                }
                analys.Add(result);

                mounthBalance.Clear();
            }

            return analys;
        }
    }
}
