package fr.eseo.poo.projet.artiste.modele.formes;

import static org.junit.Assert.assertEquals;


import java.util.Arrays;
import java.util.Collection;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;
import fr.eseo.poo.projet.artiste.modele.Coordonnees;

@RunWith(Parameterized.class)
public class LigneTestParametresPerimetre {
	private Coordonnees c1; 
	private Coordonnees c2;
	private double perimetre;
	
	public LigneTestParametresPerimetre(Coordonnees c1, Coordonnees c2, double perimetre) {
		this.c1 = c1; 
		this.c2 = c2; 
		this.perimetre = perimetre;
	}
	

	@Parameters(name= "dtLigne[{index}] : {0}, {1}, {2} ") 
	public static Collection<Object[]>dtLigne(){
		Object[][] dtLigne = new Object[][] {
			{new Coordonnees(10, 10), new Coordonnees(20, 20), 10*Math.sqrt(2)},
			{new Coordonnees(10, 10), new Coordonnees(5, 5), 5*Math.sqrt(2)},
			{new Coordonnees(10, 10), new Coordonnees(20, 5), Math.sqrt(10*10 + 5*5)},
			{new Coordonnees(10, 10), new Coordonnees(5, 20), Math.sqrt(10*10 + 5*5)},
			{new Coordonnees(52.6, 28.5), new Coordonnees(10.5, 32.6), Math.sqrt((52.6-10.5)*(52.6-10.5) + (32.6-28.5)*(32.6-28.5) )},
			{new Coordonnees(-52.6, 28.5), new Coordonnees(10.5, 32.6), Math.sqrt((-52.6-10.5)*(-52.6-10.5) + (32.6-28.5)*(32.6-28.5) )},
		};
		return Arrays.asList(dtLigne);}
	
	@Test
	public void testPerimetre() {
		LigneTestParametresPerimetre testPerimetre = new LigneTestParametresPerimetre(c1, c2, perimetre);
		Ligne ligne = new Ligne(testPerimetre.c1);
		ligne.setC2(testPerimetre.c2);
		assertEquals("Le périmètre de la ligne est bon", perimetre, ligne.perimetre(), 0.1);
	}
		
		
}
