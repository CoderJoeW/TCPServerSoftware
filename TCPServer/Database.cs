using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;
using Newtonsoft.Json;

namespace Better_Server {
    class Database {
        public static string GetIdentifier(string identifier) {
            string query = "SELECT uid FROM users WHERE uid='" + identifier + "'";

            MySqlConnection conn = MySQL.GetConn();
            conn.Open();

            using (MySqlCommand cmd = new MySqlCommand(query,conn)) {
                using(MySqlDataReader reader = cmd.ExecuteReader()) {
                    string uid = "";

                    while (reader.Read()) {
                        uid = (string)reader["uid"];
                    }

                    reader.Close();

                    conn.Close();

                    return uid;
                }
            }
        }

        public static void LogError(string errorMessage) {
            String timeStamp = lib.GetTimestamp(DateTime.Now);
            string query = "INSERT INTO error_logs SET error='" + errorMessage + "', timestamp='" + timeStamp + "'";
            
            Console.WriteLine("CUSTOM ERROR MESSAGE: " + errorMessage);

            MySqlConnection conn = MySQL.GetConn();
            conn.Open();

            using (MySqlCommand cmd = new MySqlCommand(query, conn)) {
                try {
                    cmd.ExecuteNonQuery();
                } catch (Exception e) {
                    Database.LogError(e.Message);
                }
            }

            conn.Close();
        }
    }
}
