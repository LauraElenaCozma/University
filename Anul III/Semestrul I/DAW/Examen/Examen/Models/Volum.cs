using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Examen.Models
{
    public class Volum
    {
        [Key]
        public int IdVolum { get; set; }
        [Required]
        [MinLength(2, ErrorMessage = "Denumirea trebuie sa aiba cel putin 2 caractere!"),
            MaxLength(100, ErrorMessage = "Denumirea trebuie sa aiba cel mult 100 caractere!")]
        public String Denumire { get; set; }
        public virtual ICollection<Poezie> Poezii { get; set; }
    }
}