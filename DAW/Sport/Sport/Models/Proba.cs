using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Sport.Models
{
    public class Proba
    {
        [Key]
        public int IDProba { get; set; }
        public String Denumire { get; set; }
        public DateTime Data { get; set; }
    }
}