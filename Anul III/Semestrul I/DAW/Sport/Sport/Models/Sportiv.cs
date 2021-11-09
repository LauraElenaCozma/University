using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Sport.Models
{
    public class Sportiv
    {
        [Key]
        public int IDSportiv { get; set; }
        public String Nume { get; set; }
        public String Prenume { get; set; }
        public String Tara { get; set; }
        public DateTime DataNasterii { get; set; }
        public int IDProba { get; set; }

        [NotMapped]
        public IEnumerable<SelectListItem> ListaProbe { get; set; }
    }
}